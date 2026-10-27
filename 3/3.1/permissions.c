#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "permissions.h"

void permissions_to_symbolic(mode_t permissions, char output[PERMISSION_STRING_SIZE]) {
    const char symbols[] = "rwxrwxrwx";

    for (int i = 0; i < PERMISSION_BITS; i++) {
        mode_t bit = 1 << (PERMISSION_BITS - 1 - i);

        if (permissions & bit) {
            output[i] = symbols[i];
        } else {
            output[i] = '-';
        }
    }

    output[PERMISSION_BITS] = '\0';
}

void permissions_to_binary(mode_t permissions, char output[PERMISSION_STRING_SIZE]) {
    for (int i = 0; i < PERMISSION_BITS; i++) {
        mode_t bit = 1 << (PERMISSION_BITS - 1 - i);

        if (permissions & bit) {
            output[i] = '1';
        } else {
            output[i] = '0';
        }
    }

    output[PERMISSION_BITS] = '\0';
}

static int parse_symbolic(const char input[], mode_t *permissions) {
    const char symbols[] = "rwxrwxrwx";
    mode_t result = 0;

    if (strlen(input) != PERMISSION_BITS) {
        return 0;
    }

    for (int i = 0; i < PERMISSION_BITS; i++) {
        if (input[i] == symbols[i]) {
            result |= 1 << (PERMISSION_BITS - 1 - i);
        } else if (input[i] != '-') {
            return 0;
        }
    }

    *permissions = result;

    return 1;
}

static int parse_numeric(const char input[], mode_t *permissions) {
    char *end;
    long result = strtol(input, &end, 8);

    if (end == input || *end != '\0' || result < 0 || result > PERMISSION_MASK) {
        return 0;
    }

    *permissions = (mode_t)result;

    return 1;
}

int parse_permissions(const char input[], mode_t *permissions) {
    if (parse_numeric(input, permissions)) {
        return 1;
    }

    return parse_symbolic(input, permissions);
}

int get_file_permissions(const char path[], mode_t *permissions) {
    struct stat file_info;

    if (stat(path, &file_info) == -1) {
        return 0;
    }

    *permissions = file_info.st_mode & PERMISSION_MASK;

    return 1;
}

static int apply_single_command(mode_t *permissions, const char command[]) {
    mode_t target_mask = 0;
    mode_t permission_value = 0;
    int i = 0;

    while (command[i] != '\0' && command[i] != '+' && command[i] != '-' && command[i] != '=') {
        switch (command[i]) {
            case 'u':
                target_mask |= USER_PERMISSION_MASK;
                break;
            case 'g':
                target_mask |= GROUP_PERMISSION_MASK;
                break;
            case 'o':
                target_mask |= OTHER_PERMISSION_MASK;
                break;
            case 'a':
                target_mask |= PERMISSION_MASK;
                break;
            default:
                return 0;
        }

        i++;
    }

    if (i == 0 || command[i] == '\0') {
        return 0;
    }

    char operation = command[i];
    i++;

    if (command[i] == '\0' && operation != '=') {
        return 0;
    }

    while (command[i] != '\0') {
        switch (command[i]) {
            case 'r':
                permission_value |= 4;
                break;
            case 'w':
                permission_value |= 2;
                break;
            case 'x':
                permission_value |= 1;
                break;
            default:
                return 0;
        }

        i++;
    }

    mode_t permission_bits = 0;

    if (target_mask & USER_PERMISSION_MASK) {
        permission_bits |= permission_value << 6;
    }

    if (target_mask & GROUP_PERMISSION_MASK) {
        permission_bits |= permission_value << 3;
    }

    if (target_mask & OTHER_PERMISSION_MASK) {
        permission_bits |= permission_value;
    }

    switch (operation) {
        case '+':
            *permissions |= permission_bits;
            break;
        case '-':
            *permissions &= ~permission_bits;
            break;
        case '=':
            *permissions = (*permissions & ~target_mask) | permission_bits;
            break;
    }

    return 1;
}

int apply_permissions_command(mode_t current_permissions, const char command[], mode_t *new_permissions) {
    size_t length = strlen(command);

    if (length == 0 || length >= COMMAND_BUFFER_SIZE) {
        return 0;
    }

    char command_copy[COMMAND_BUFFER_SIZE];
    strcpy(command_copy, command);

    current_permissions &= PERMISSION_MASK;
    char *part = command_copy;

    while (part != NULL) {
        char *comma = strchr(part, ',');

        if (comma != NULL) {
            *comma = '\0';
        }

        if (part[0] == '\0' || !apply_single_command(&current_permissions, part)) {
            return 0;
        }

        if (comma == NULL) {
            part = NULL;
        } else {
            part = comma + 1;
        }
    }

    *new_permissions = current_permissions;

    return 1;
}
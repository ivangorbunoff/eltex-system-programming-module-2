#include <stdio.h>
#include <string.h>
#include "permissions.h"
#include "ui.h"

static void read_line(char output[], int size) {
    if (fgets(output, size, stdin) == NULL) {
        output[0] = '\0';
        return;
    }

    size_t length = strlen(output);

    if (length > 0 && output[length - 1] == '\n') {
        output[length - 1] = '\0';
    } else {
        int character;

        while ((character = getchar()) != '\n' && character != EOF) {
        }
    }
}

static int read_number(int min, int max) {
    char input[INPUT_BUFFER_SIZE];
    int number;
    char extra_character;

    while (1) {
        read_line(input, sizeof(input));

        if (sscanf(input, "%d %c", &number, &extra_character) == 1 && number >= min && number <= max) {
            return number;
        }

        printf("Введите число от %d до %d: ", min, max);
    }
}

MenuChoice show_menu(void) {
    printf("\n------------------------\n");
    printf("\nПрава доступа к файлам\n\n");
    printf("1. Ввести права доступа\n");
    printf("2. Получить права файла\n");
    printf("3. Изменить текущие права\n");
    printf("0. Выйти\n");
    printf("\nВыберите действие: ");

    return (MenuChoice)read_number(
        MENU_EXIT,
        MENU_MODIFY_PERMISSIONS
    );
}

void input_permissions(char input[], int size) {
    printf("Введите права доступа ");

    read_line(input, size);
}

void input_file_path(char path[], int size) {
    printf("Введите имя или путь к файлу: ");
    read_line(path, size);
}

void input_command(char command[], int size) {
    printf("Введите команду ");
    read_line(command, size);
}

void show_permissions(mode_t permissions) {
    char symbolic[PERMISSION_STRING_SIZE];
    char binary[PERMISSION_STRING_SIZE];

    permissions_to_symbolic(permissions, symbolic);
    permissions_to_binary(permissions, binary);

    printf("\nБуквенное представление: %s\n", symbolic);
    printf("Цифровое представление: %03o\n", (unsigned int)permissions);
    printf("Битовое представление: %s\n", binary);
}

void show_message(const char message[]) {
    printf("%s\n", message);
}
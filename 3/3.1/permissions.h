#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include <sys/types.h>

#define PERMISSION_BITS 9
#define PERMISSION_STRING_SIZE (PERMISSION_BITS + 1)
#define PERMISSION_MASK 0777
#define USER_PERMISSION_MASK 0700
#define GROUP_PERMISSION_MASK 0070
#define OTHER_PERMISSION_MASK 0007
#define COMMAND_BUFFER_SIZE 100

int parse_permissions(const char input[], mode_t *permissions);

void permissions_to_symbolic(mode_t permissions, char output[PERMISSION_STRING_SIZE]);

void permissions_to_binary(mode_t permissions, char output[PERMISSION_STRING_SIZE]);

int get_file_permissions(const char path[], mode_t *permissions);

int apply_permissions_command(mode_t current_permissions, const char command[], mode_t *new_permissions);

#endif
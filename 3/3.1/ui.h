#ifndef UI_H
#define UI_H

#include <sys/types.h>

#define INPUT_BUFFER_SIZE 100

typedef enum {
    MENU_EXIT = 0,
    MENU_INPUT_PERMISSIONS,
    MENU_FILE_PERMISSIONS,
    MENU_MODIFY_PERMISSIONS
} MenuChoice;

MenuChoice show_menu(void);

void input_permissions(char input[], int size);

void input_file_path(char path[], int size);

void input_command(char command[], int size);

void show_permissions(mode_t permissions);

void show_message(const char message[]);

#endif

#include "permissions.h"
#include "ui.h"

int main(void) {
    mode_t current_permissions = 0;
    int permissions_are_set = 0;
    char input[INPUT_BUFFER_SIZE];

    while (1) {
        MenuChoice choice = show_menu();

        if (choice == MENU_EXIT) {
            break;
        }

        switch (choice) {
            case MENU_INPUT_PERMISSIONS:
                input_permissions(input, sizeof(input));

                if (parse_permissions(input, &current_permissions)) {
                    permissions_are_set = 1;
                    show_permissions(current_permissions);
                } else {
                    show_message("Некорректные права доступа.");
                }

                break;

            case MENU_FILE_PERMISSIONS:
                input_file_path(input, sizeof(input));

                if (get_file_permissions(input, &current_permissions)) {
                    permissions_are_set = 1;
                    show_permissions(current_permissions);
                } else {
                    show_message("Не удалось получить права файла.");
                }

                break;

            case MENU_MODIFY_PERMISSIONS:
                if (!permissions_are_set) {
                    show_message("Сначала введите права или выберите файл.");
                    break;
                }

                show_message("Текущие права:");
                show_permissions(current_permissions);
                input_command(input, sizeof(input));

                if (apply_permissions_command(current_permissions, input, &current_permissions)) {
                    show_message("Новые права:");
                    show_permissions(current_permissions);
                } else {
                    show_message("Некорректная команда.");
                }

                break;

            case MENU_EXIT:
                break;
        }
    }

    return 0;
}

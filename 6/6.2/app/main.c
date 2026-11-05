#include "contacts.h"
#include "ui.h"

int main(void) {
    ContactList contacts = {0};
    MenuChoice choice;

    do {
        choice = show_menu();

        switch (choice) {
            case MENU_SHOW_CONTACTS:
                show_contacts(&contacts);
                break;

            case MENU_ADD_CONTACT: {
                Contact new_contact = input_contact();

                if (add_contact(&contacts, new_contact)) {
                    show_message("Контакт добавлен.");
                } else {
                    show_message("Не удалось добавить контакт.");
                }

                break;
            }

            case MENU_EDIT_CONTACT: {
                if (contacts.count == 0) {
                    show_message("Телефонная книга пуста.");
                    break;
                }

                show_contacts(&contacts);

                int index = input_contact_index(contacts.count);
                Contact edited_contact;

                if (!get_contact(&contacts, index, &edited_contact)) {
                    show_message("Не удалось получить контакт.");
                    break;
                }

                edited_contact = input_contact_changes(edited_contact);

                if (edit_contact(&contacts, index, edited_contact)) {
                    show_message("Контакт изменён.");
                } else {
                    show_message("Не удалось изменить контакт.");
                }

                break;
            }

            case MENU_DELETE_CONTACT: {
                if (contacts.count == 0) {
                    show_message("Телефонная книга пуста.");
                    break;
                }

                show_contacts(&contacts);

                int index = input_contact_index(contacts.count);

                if (delete_contact(&contacts, index)) {
                    show_message("Контакт удалён.");
                } else {
                    show_message("Не удалось удалить контакт.");
                }

                break;
            }

            case MENU_EXIT:
                show_message("Завершение программы.");
                break;
        }
    } while (choice != MENU_EXIT);

    clear_contacts(&contacts);

    return 0;
}

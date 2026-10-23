#include "contacts.h"
#include "ui.h"

int main(void) {
    Contact contacts[MAX_CONTACTS] = {0};
    int contact_count = 0;
    MenuChoice choice;

    do {
        choice = show_menu();

        switch (choice) {
            case MENU_SHOW_CONTACTS:
                show_contacts(contacts, contact_count);
                break;

            case MENU_ADD_CONTACT: {
                if (contact_count >= MAX_CONTACTS) {
                    show_message("Телефонная книга заполнена.");
                    break;
                }

                Contact new_contact = input_contact();

                if (add_contact(contacts, &contact_count, new_contact)) {
                    show_message("Контакт добавлен.");
                } else {
                    show_message("Не удалось добавить контакт.");
                }

                break;
            }

            case MENU_EDIT_CONTACT: {
                if (contact_count == 0) {
                    show_message("Телефонная книга пуста.");
                    break;
                }

                show_contacts(contacts, contact_count);

                int index = input_contact_index(contact_count);

                Contact edited_contact = input_contact_changes(contacts[index]);

                if (edit_contact(contacts, contact_count, index, edited_contact)) {
                    show_message("Контакт изменён.");
                } else {
                    show_message("Не удалось изменить контакт.");
                }

                break;
            }

            case MENU_DELETE_CONTACT: {
                if (contact_count == 0) {
                    show_message("Телефонная книга пуста.");
                    break;
                }

                show_contacts(contacts, contact_count);

                int index = input_contact_index(contact_count);

                if (delete_contact(contacts, &contact_count, index)) {
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

    return 0;
}

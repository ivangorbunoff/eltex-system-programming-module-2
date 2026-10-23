#ifndef UI_H
#define UI_H

#include "contacts.h"

typedef enum {
    MENU_EXIT = 0,
    MENU_SHOW_CONTACTS,
    MENU_ADD_CONTACT,
    MENU_EDIT_CONTACT,
    MENU_DELETE_CONTACT
} MenuChoice;

MenuChoice show_menu(void);

void show_contacts(
    const Contact contacts[],
    int contact_count
);

Contact input_contact(void);

Contact input_contact_changes(Contact contact);

int input_contact_index(int contact_count);

void show_message(const char message[]);

#endif

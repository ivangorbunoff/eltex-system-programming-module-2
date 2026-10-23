#include "contacts.h"

int add_contact(Contact contacts[], int *contact_count, Contact new_contact) {
    if (*contact_count >= MAX_CONTACTS) {
        return 0;
    }

    if (new_contact.last_name[0] == '\0' ||
        new_contact.first_name[0] == '\0') {
        return 0;
    }

    contacts[*contact_count] = new_contact;
    (*contact_count)++;

    return 1;
}

int edit_contact(Contact contacts[], int contact_count, int index, Contact edited_contact) {
    if (index < 0 || index >= contact_count) {
        return 0;
    }

    if (edited_contact.last_name[0] == '\0' ||
        edited_contact.first_name[0] == '\0') {
        return 0;
    }

    contacts[index] = edited_contact;

    return 1;
}

int delete_contact(Contact contacts[], int *contact_count, int index) {
    if (index < 0 || index >= *contact_count) {
        return 0;
    }

    for (int i = index; i < (*contact_count - 1); i++) {
        contacts[i] = contacts[i + 1];
    }

    (*contact_count)--;

    return 1;
}
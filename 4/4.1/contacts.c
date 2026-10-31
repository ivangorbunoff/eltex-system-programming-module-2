#include <stdlib.h>
#include <string.h>
#include "contacts.h"

static int compare_contacts(const Contact* first, const Contact* second) {
    int result = strcmp(first->last_name, second->last_name);

    if (result != 0) {
        return result;
    }

    return strcmp(first->first_name, second->first_name);
}

static void insert_node_sorted(ContactList* list, ContactNode* node) {
    node->prev = NULL;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
        return;
    }

    if (compare_contacts(&node->contact, &list->head->contact) < 0) {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
        return;
    }

    if (compare_contacts(&node->contact, &list->tail->contact) >= 0) {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
        return;
    }

    ContactNode* current = list->head->next;

    while (compare_contacts(&node->contact, &current->contact) >= 0) {
        current = current->next;
    }

    node->next = current;
    node->prev = current->prev;
    current->prev->next = node;
    current->prev = node;
}

static void detach_node(ContactList* list, ContactNode* node) {
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    node->prev = NULL;
    node->next = NULL;
}

static ContactNode* get_node_at(const ContactList* list, int index) {
    if (list == NULL || index < 0 || index >= list->count) {
        return NULL;
    }

    ContactNode* node;

    if (index < list->count / 2) {
        node = list->head;

        for (int i = 0; i < index; i++) {
            node = node->next;
        }
    } else {
        node = list->tail;

        for (int i = list->count - 1; i > index; i--) {
            node = node->prev;
        }
    }

    return node;
}

int get_contact(const ContactList* list, int index, Contact* contact) {
    if (contact == NULL) {
        return 0;
    }

    ContactNode* node = get_node_at(list, index);

    if (node == NULL) {
        return 0;
    }

    *contact = node->contact;

    return 1;
}

int add_contact(ContactList* list, Contact new_contact) {
    if (list == NULL || new_contact.last_name[0] == '\0' || new_contact.first_name[0] == '\0') {
        return 0;
    }

    ContactNode* node = malloc(sizeof(ContactNode));

    if (node == NULL) {
        return 0;
    }

    node->contact = new_contact;

    insert_node_sorted(list, node);
    list->count++;

    return 1;
}

int edit_contact(ContactList* list, int index, Contact edited_contact) {
    if (list == NULL || edited_contact.last_name[0] == '\0' || edited_contact.first_name[0] == '\0') {
        return 0;
    }

    ContactNode* node = get_node_at(list, index);

    if (node == NULL) {
        return 0;
    }

    detach_node(list, node);
    node->contact = edited_contact;
    insert_node_sorted(list, node);

    return 1;
}

int delete_contact(ContactList* list, int index) {
    ContactNode* node = get_node_at(list, index);

    if (node == NULL) {
        return 0;
    }

    detach_node(list, node);
    free(node);
    list->count--;

    return 1;
}

void clear_contacts(ContactList* list) {
    if (list == NULL) {
        return;
    }

    ContactNode* node = list->head;

    while (node != NULL) {
        ContactNode* next = node->next;
        free(node);
        node = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
}
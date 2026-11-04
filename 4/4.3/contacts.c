#include <stdlib.h>
#include <string.h>
#include "contacts.h"

static int get_height(const ContactNode* node) {
    return node == NULL ? 0 : node->height;
}

static int max_int(int first, int second) {
    return first > second ? first : second;
}

static void update_height(ContactNode* node) {
    if (node == NULL) {
        return;
    }

    int left_height = get_height(node->left);
    int right_height = get_height(node->right);

    node->height = 1 + max_int(left_height, right_height);
}

static int get_balance(const ContactNode* node) {
    if (node == NULL) {
        return 0;
    }

    return get_height(node->left) - get_height(node->right);
}

static int compare_names(const Contact* first, const Contact* second) {
    int result = strcmp(first->last_name, second->last_name);

    if (result != 0) {
        return result;
    }

    result = strcmp(first->first_name, second->first_name);

    if (result != 0) {
        return result;
    }

    return strcmp(first->middle_name, second->middle_name);
}

static int compare_keys(const Contact* first, unsigned int first_id, const Contact* second, unsigned int second_id) {
    int result = compare_names(first, second);

    if (result != 0) {
        return result;
    }

    if (first_id < second_id) {
        return -1;
    }

    if (first_id > second_id) {
        return 1;
    }

    return 0;
}

static ContactNode* create_node(Contact contact, unsigned int id) {
    ContactNode* node = malloc(sizeof(ContactNode));

    if (node == NULL) {
        return NULL;
    }

    node->contact = contact;
    node->id = id;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;

    return node;
}

static ContactNode* rotate_right(ContactNode* node) {
    if (node == NULL || node->left == NULL) {
        return node;
    }

    ContactNode* new_root = node->left;
    ContactNode* moved_subtree = new_root->right;

    new_root->right = node;
    node->left = moved_subtree;

    update_height(node);
    update_height(new_root);

    return new_root;
}

static ContactNode* rotate_left(ContactNode* node) {
    if (node == NULL || node->right == NULL) {
        return node;
    }

    ContactNode* new_root = node->right;
    ContactNode* moved_subtree = new_root->left;

    new_root->left = node;
    node->right = moved_subtree;

    update_height(node);
    update_height(new_root);

    return new_root;
}

static ContactNode* balance_node(ContactNode* node) {
    if (node == NULL) {
        return NULL;
    }

    update_height(node);

    int balance = get_balance(node);

    if (balance > 1) {
        if (get_balance(node->left) < 0) {
            node->left = rotate_left(node->left);
        }

        return rotate_right(node);
    }

    if (balance < -1) {
        if (get_balance(node->right) > 0) {
            node->right = rotate_right(node->right);
        }

        return rotate_left(node);
    }

    return node;
}

static ContactNode* insert_node(ContactNode* node, const Contact* contact, unsigned int id, int* inserted) {
    if (node == NULL) {
        ContactNode* new_node = create_node(*contact, id);

        if (new_node != NULL) {
            *inserted = 1;
        }

        return new_node;
    }

    int comparison = compare_keys(contact, id, &node->contact, node->id);

    if (comparison < 0) {
        node->left = insert_node(node->left, contact, id, inserted);
    } else if (comparison > 0) {
        node->right = insert_node(node->right, contact, id, inserted);
    } else {
        return node;
    }

    return balance_node(node);
}

int add_contact(ContactTree* tree, Contact new_contact) {
    if (tree == NULL || new_contact.last_name[0] == '\0' || new_contact.first_name[0] == '\0') {
        return 0;
    }

    int inserted = 0;
    unsigned int id = tree->next_id;

    tree->root = insert_node(tree->root, &new_contact, id, &inserted);

    if (!inserted) {
        return 0;
    }

    tree->count++;
    tree->next_id++;

    return 1;
}

static ContactNode* get_node_by_index(ContactNode* node, int target_index, int* current_index) {
    if (node == NULL) {
        return NULL;
    }

    ContactNode* result = get_node_by_index(node->left, target_index, current_index);

    if (result != NULL) {
        return result;
    }

    if (*current_index == target_index) {
        return node;
    }

    (*current_index)++;

    return get_node_by_index(node->right, target_index, current_index);
}

int get_contact(const ContactTree* tree, int index, Contact* contact) {
    if (tree == NULL || contact == NULL || index < 0 || index >= tree->count) {
        return 0;
    }

    int current_index = 0;
    const ContactNode* node = get_node_by_index(tree->root, index, &current_index);

    if (node == NULL) {
        return 0;
    }

    *contact = node->contact;

    return 1;
}

static ContactNode* get_max_node(ContactNode* node) {
    if (node == NULL) {
        return NULL;
    }

    while (node->right != NULL) {
        node = node->right;
    }

    return node;
}

static ContactNode* delete_node(ContactNode* node, const Contact* contact, unsigned int id, int* deleted) {
    if (node == NULL) {
        return NULL;
    }

    int comparison = compare_keys(contact, id, &node->contact, node->id);

    if (comparison < 0) {
        node->left = delete_node(node->left, contact, id, deleted);
    } else if (comparison > 0) {
        node->right = delete_node(node->right, contact, id, deleted);
    } else {
        *deleted = 1;

        if (node->left == NULL) {
            ContactNode* right_child = node->right;

            free(node);

            return right_child;
        }

        if (node->right == NULL) {
            ContactNode* left_child = node->left;

            free(node);

            return left_child;
        }

        ContactNode* max_node = get_max_node(node->left);

        node->contact = max_node->contact;
        node->id = max_node->id;

        int ignored = 0;

        node->left = delete_node(node->left, &node->contact, node->id, &ignored);
    }

    return balance_node(node);
}

int delete_contact(ContactTree* tree, int index) {
    if (tree == NULL || index < 0 || index >= tree->count) {
        return 0;
    }

    int current_index = 0;
    const ContactNode* target = get_node_by_index(tree->root, index, &current_index);

    if (target == NULL) {
        return 0;
    }

    Contact target_contact = target->contact;
    unsigned int target_id = target->id;
    int deleted = 0;

    tree->root = delete_node(tree->root, &target_contact, target_id, &deleted);

    if (!deleted) {
        return 0;
    }

    tree->count--;

    return 1;
}

int edit_contact(ContactTree* tree, int index, Contact edited_contact) {
    if (tree == NULL || index < 0 || index >= tree->count ||
        edited_contact.last_name[0] == '\0' || edited_contact.first_name[0] == '\0') {
        return 0;
    }

    int current_index = 0;
    ContactNode* target = get_node_by_index(tree->root, index, &current_index);

    if (target == NULL) {
        return 0;
    }

    Contact old_contact = target->contact;
    unsigned int target_id = target->id;

    if (compare_names(&old_contact, &edited_contact) == 0) {
        target->contact = edited_contact;

        return 1;
    }

    int inserted = 0;

    tree->root = insert_node(tree->root, &edited_contact, target_id, &inserted);

    if (!inserted) {
        return 0;
    }

    int deleted = 0;

    tree->root = delete_node(tree->root, &old_contact, target_id, &deleted);

    return deleted;
}

static void clear_nodes(ContactNode* node) {
    if (node == NULL) {
        return;
    }

    clear_nodes(node->left);
    clear_nodes(node->right);

    free(node);
}

void clear_contacts(ContactTree* tree) {
    if (tree == NULL) {
        return;
    }

    clear_nodes(tree->root);

    tree->root = NULL;
    tree->count = 0;
    tree->next_id = 0;
}
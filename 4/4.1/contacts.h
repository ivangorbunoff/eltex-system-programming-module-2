#ifndef CONTACTS_H
#define CONTACTS_H

#define MAX_NAME_LENGTH 100
#define MAX_WORK_LENGTH 100
#define MAX_POSITION_LENGTH 100
#define MAX_OPTIONAL_TEXT_LENGTH 100

#define MAX_PHONES 3
#define MAX_PHONE_LENGTH 20

#define MAX_EMAILS 3
#define MAX_EMAIL_LENGTH 100

#define MAX_SOCIAL_LINKS 3
#define MAX_MESSENGER_PROFILES 3
#define MAX_LINK_LENGTH 200

typedef struct {
    char last_name[MAX_NAME_LENGTH];
    char first_name[MAX_NAME_LENGTH];
    char middle_name[MAX_NAME_LENGTH];

    char workplace[MAX_WORK_LENGTH];
    char position[MAX_POSITION_LENGTH];

    char phones[MAX_PHONES][MAX_PHONE_LENGTH];
    int phone_count;

    char emails[MAX_EMAILS][MAX_EMAIL_LENGTH];
    int email_count;

    char social_links[MAX_SOCIAL_LINKS][MAX_LINK_LENGTH];
    int social_link_count;

    char messenger_profiles[MAX_MESSENGER_PROFILES][MAX_LINK_LENGTH];
    int messenger_profile_count;
} Contact;

typedef struct ContactNode {
    Contact contact;
    struct ContactNode *prev;
    struct ContactNode *next;
} ContactNode;

typedef struct {
    ContactNode *head;
    ContactNode *tail;
    int count;
} ContactList;

int add_contact(
    ContactList *list,
    Contact new_contact
);

int get_contact(
    const ContactList *list,
    int index,
    Contact *contact
);

int edit_contact(
    ContactList *list,
    int index,
    Contact edited_contact
);

int delete_contact(
    ContactList *list,
    int index
);

void clear_contacts(ContactList *list);

#endif

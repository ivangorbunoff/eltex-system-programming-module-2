#include <stdio.h>
#include <string.h>

#include "ui.h"

static void read_line(char text[], int size) {
    if (fgets(text, size, stdin) == NULL) {
        text[0] = '\0';
        return;
    }

    size_t length = strlen(text);

    if (length > 0 && text[length - 1] == '\n') {
        text[length - 1] = '\0';
    } else {
        int character;

        while ((character = getchar()) != '\n' && character != EOF) {
        }
    }
}

static int read_number(int min, int max) {
    char input[100];
    int number;
    char extra_character;

    while (1) {
        read_line(input, sizeof(input));

        if (sscanf(input, "%d %c", &number, &extra_character) == 1 && number >= min && number <= max) {
            return number;
        }

        printf("Введите число от %d до %d: ", min, max);
    }
}

static void read_optional_text(char text[], int size) {
    char input[MAX_OPTIONAL_TEXT_LENGTH];

    read_line(input, size);

    if (input[0] == '\0') {
        return;
    }

    if (strcmp(input, "0") == 0) {
        text[0] = '\0';
        return;
    }

    strcpy(text, input);
}

static int read_optional_count(int max, int *count) {
    char input[100];
    int number;
    char extra_character;

    while (1) {
        read_line(input, sizeof(input));

        if (input[0] == '\0') {
            return 0;
        }

        if (sscanf(input, "%d %c", &number, &extra_character) == 1 && number >= 0 && number <= max) {
            *count = number;
            return 1;
        }

        printf("Введите число от 0 до %d или нажмите Enter: ", max);
    }
}

MenuChoice show_menu(void) {
    printf("\n----------------\n");
    printf("\nТелефонная книга\n\n");
    printf("1. Показать контакты\n");
    printf("2. Добавить контакт\n");
    printf("3. Редактировать контакт\n");
    printf("4. Удалить контакт\n");
    printf("0. Выйти\n");
    printf("\nВыберите действие: ");

    return (MenuChoice) read_number(
        MENU_EXIT,
        MENU_DELETE_CONTACT
    );
}

Contact input_contact(void) {
    Contact contact = {0};

    printf("\nДобавление контакта\n\n");

    do {
        printf("Фамилия: ");
        read_line(contact.last_name, sizeof(contact.last_name));

        if (contact.last_name[0] == '\0') {
            printf("Фамилия обязательна.\n");
        }
    } while (contact.last_name[0] == '\0');

    do {
        printf("Имя: ");
        read_line(contact.first_name, sizeof(contact.first_name));

        if (contact.first_name[0] == '\0') {
            printf("Имя обязательно.\n");
        }
    } while (contact.first_name[0] == '\0');

    printf("Отчество (Enter или 0 — пропустить): ");
    read_optional_text(contact.middle_name, sizeof(contact.middle_name));

    printf("Место работы (Enter или 0 — пропустить): ");
    read_optional_text(contact.workplace, sizeof(contact.workplace));

    printf("Должность (Enter или 0 — пропустить): ");
    read_optional_text(contact.position, sizeof(contact.position));

    printf("Количество телефонов (0-%d, Enter — пропустить): ", MAX_PHONES);
    read_optional_count(MAX_PHONES, &contact.phone_count);

    for (int i = 0; i < contact.phone_count; i++) {
        do {
            printf("Телефон %d: ", i + 1);
            read_line(
                contact.phones[i],
                sizeof(contact.phones[i])
            );

            if (contact.phones[i][0] == '\0') {
                printf("Номер телефона не может быть пустым.\n");
            }
        } while (contact.phones[i][0] == '\0');
    }

    printf("Количество адресов электронной почты (0-%d, Enter — пропустить): ", MAX_EMAILS);
    read_optional_count(MAX_EMAILS, &contact.email_count);

    for (int i = 0; i < contact.email_count; i++) {
        do {
            printf("Электронная почта %d: ", i + 1);
            read_line(
                contact.emails[i],
                sizeof(contact.emails[i])
            );

            if (contact.emails[i][0] == '\0') {
                printf("Адрес электронной почты не может быть пустым.\n");
            }
        } while (contact.emails[i][0] == '\0');
    }

    printf("Количество ссылок на социальные сети (0-%d, Enter — пропустить): ", MAX_SOCIAL_LINKS);
    read_optional_count(MAX_SOCIAL_LINKS, &contact.social_link_count);

    for (int i = 0; i < contact.social_link_count; i++) {
        do {
            printf("Ссылка на социальную сеть %d: ", i + 1);
            read_line(
                contact.social_links[i],
                sizeof(contact.social_links[i])
            );

            if (contact.social_links[i][0] == '\0') {
                printf("Ссылка не может быть пустой.\n");
            }
        } while (contact.social_links[i][0] == '\0');
    }

    printf("Количество профилей в мессенджерах (0-%d, Enter — пропустить): ", MAX_MESSENGER_PROFILES);
    read_optional_count(MAX_MESSENGER_PROFILES, &contact.messenger_profile_count);

    for (int i = 0; i < contact.messenger_profile_count; i++) {
        do {
            printf("Профиль в мессенджере %d: ", i + 1);
            read_line(
                contact.messenger_profiles[i],
                sizeof(contact.messenger_profiles[i])
            );

            if (contact.messenger_profiles[i][0] == '\0') {
                printf("Профиль не может быть пустым.\n");
            }
        } while (contact.messenger_profiles[i][0] == '\0');
    }

    return contact;
}

void show_contacts(const Contact contacts[], int contact_count) {
    printf("\nСписок контактов\n");

    if (contact_count == 0) {
        printf("Телефонная книга пуста.\n");
        return;
    }

    for (int i = 0; i < contact_count; i++) {
        printf("\n%d. %s %s", i + 1, contacts[i].last_name, contacts[i].first_name);

        if (contacts[i].middle_name[0] != '\0') {
            printf(" %s", contacts[i].middle_name);
        }

        printf("\n");

        if (contacts[i].workplace[0] != '\0') {
            printf("   Место работы: %s\n", contacts[i].workplace);
        }

        if (contacts[i].position[0] != '\0') {
            printf("   Должность: %s\n", contacts[i].position);
        }

        for (int j = 0; j < contacts[i].phone_count; j++) {
            printf("   Телефон %d: %s\n", j + 1, contacts[i].phones[j]);
        }

        for (int j = 0; j < contacts[i].email_count; j++) {
            printf("   Электронная почта %d: %s\n", j + 1, contacts[i].emails[j]);
        }

        for (int j = 0; j < contacts[i].social_link_count; j++) {
            printf("   Социальная сеть %d: %s\n", j + 1, contacts[i].social_links[j]);
        }

        for (int j = 0; j < contacts[i].messenger_profile_count; j++) {
            printf("   Мессенджер %d: %s\n", j + 1, contacts[i].messenger_profiles[j]);
        }
    }

    printf("\n");
}

int input_contact_index(int contact_count) {
    if (contact_count <= 0) {
        return -1;
    }

    printf("Выберите контакт (1-%d): ", contact_count);

    return read_number(1, contact_count) - 1;
}

void show_message(const char message[]) {
    printf("%s\n", message);
}

Contact input_contact_changes(Contact contact) {
    int choice;

    do {
        printf("\nРедактирование контакта\n\n");
        printf("1. Фамилия: %s\n", contact.last_name);
        printf("2. Имя: %s\n", contact.first_name);
        printf("3. Отчество: %s\n", contact.middle_name);
        printf("4. Место работы: %s\n", contact.workplace);
        printf("5. Должность: %s\n", contact.position);
        printf("6. Телефоны:\n");

        if (contact.phone_count == 0) {
            printf("   Не указаны\n");
        } else {
            for (int i = 0; i < contact.phone_count; i++) {
                printf("   %d. %s\n", i + 1, contact.phones[i]);
            }
        }

        printf("7. Электронная почта:\n");

        if (contact.email_count == 0) {
            printf("   Не указана\n");
        } else {
            for (int i = 0; i < contact.email_count; i++) {
                printf("   %d. %s\n", i + 1, contact.emails[i]);
            }
        }

        printf("8. Социальные сети:\n");

        if (contact.social_link_count == 0) {
            printf("   Не указаны\n");
        } else {
            for (int i = 0; i < contact.social_link_count; i++) {
                printf("   %d. %s\n", i + 1, contact.social_links[i]);
            }
        }

        printf("9. Мессенджеры:\n");

        if (contact.messenger_profile_count == 0) {
            printf("   Не указаны\n");
        } else {
            for (int i = 0; i < contact.messenger_profile_count; i++) {
                printf(
                    "   %d. %s\n",
                    i + 1,
                    contact.messenger_profiles[i]
                );
            }
        }

        printf("0. Сохранить изменения\n");
        printf("\nВыберите поле: ");

        choice = read_number(0, 9);

        switch (choice) {
            case 1:
                do {
                    printf("Новая фамилия: ");
                    read_line(
                        contact.last_name,
                        sizeof(contact.last_name)
                    );

                    if (contact.last_name[0] == '\0') {
                        printf("Фамилия обязательна.\n");
                    }
                } while (contact.last_name[0] == '\0');

                break;

            case 2:
                do {
                    printf("Новое имя: ");
                    read_line(
                        contact.first_name,
                        sizeof(contact.first_name)
                    );

                    if (contact.first_name[0] == '\0') {
                        printf("Имя обязательно.\n");
                    }
                } while (contact.first_name[0] == '\0');

                break;

            case 3:
                printf("Новое отчество (Enter — оставить, 0 — удалить): ");
                read_optional_text(
                    contact.middle_name,
                    sizeof(contact.middle_name)
                );
                break;

            case 4:
                printf("Новое место работы (Enter — оставить, 0 — удалить): ");
                read_optional_text(
                    contact.workplace,
                    sizeof(contact.workplace)
                );
                break;

            case 5:
                printf("Новая должность (Enter — оставить, 0 — удалить): ");
                read_optional_text(
                    contact.position,
                    sizeof(contact.position)
                );
                break;

            case 6:
                printf("Новое количество телефонов (0-%d, Enter — оставить): ", MAX_PHONES);

                if (!read_optional_count(MAX_PHONES, &contact.phone_count)) {
                    break;
                }

                for (int i = 0; i < contact.phone_count; i++) {
                    do {
                        printf("Телефон %d: ", i + 1);
                        read_line(
                            contact.phones[i],
                            sizeof(contact.phones[i])
                        );

                        if (contact.phones[i][0] == '\0') {
                            printf("Номер телефона не может быть пустым.\n");
                        }
                    } while (contact.phones[i][0] == '\0');
                }

                break;

            case 7:
                printf(
                    "Новое количество адресов электронной почты (0-%d, Enter — оставить): ",
                    MAX_EMAILS
                );

                if (!read_optional_count(MAX_EMAILS, &contact.email_count)) {
                    break;
                }

                for (int i = 0; i < contact.email_count; i++) {
                    do {
                        printf("Электронная почта %d: ", i + 1);
                        read_line(
                            contact.emails[i],
                            sizeof(contact.emails[i])
                        );

                        if (contact.emails[i][0] == '\0') {
                            printf(
                                "Адрес электронной почты не может быть пустым.\n"
                            );
                        }
                    } while (contact.emails[i][0] == '\0');
                }

                break;

            case 8:
                printf(
                    "Новое количество ссылок на социальные сети (0-%d, Enter — оставить): ",
                    MAX_SOCIAL_LINKS
                );

                if (!read_optional_count(MAX_SOCIAL_LINKS, &contact.social_link_count)) {
                    break;
                }

                for (int i = 0; i < contact.social_link_count; i++) {
                    do {
                        printf("Ссылка на социальную сеть %d: ", i + 1);
                        read_line(
                            contact.social_links[i],
                            sizeof(contact.social_links[i])
                        );

                        if (contact.social_links[i][0] == '\0') {
                            printf("Ссылка не может быть пустой.\n");
                        }
                    } while (contact.social_links[i][0] == '\0');
                }

                break;

            case 9:
                printf(
                    "Новое количество профилей в мессенджерах (0-%d, Enter — оставить): ",
                    MAX_MESSENGER_PROFILES
                );

                if (!read_optional_count(MAX_MESSENGER_PROFILES, &contact.messenger_profile_count)) {
                    break;
                }

                for (int i = 0; i < contact.messenger_profile_count; i++) {
                    do {
                        printf("Профиль в мессенджере %d: ", i + 1);
                        read_line(
                            contact.messenger_profiles[i],
                            sizeof(contact.messenger_profiles[i])
                        );

                        if (contact.messenger_profiles[i][0] == '\0') {
                            printf("Профиль не может быть пустым.\n");
                        }
                    } while (
                        contact.messenger_profiles[i][0] == '\0'
                    );
                }

                break;
        }
    } while (choice != 0);

    return contact;
}

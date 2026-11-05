#include <dlfcn.h>
#include <stdio.h>

static void clear_input_buffer(void) {
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
    }
}

typedef int (*Operation)(double, double, double*);

typedef struct {
    const char* name;
    const char* library_path;
    const char* function_name;
    Operation function;
    void* handle;
} Command;

static void unload_commands(Command commands[], int command_count) {
    for (int i = 0; i < command_count; i++) {
        if (commands[i].handle != NULL) {
            dlclose(commands[i].handle);
        }

        commands[i].handle = NULL;
        commands[i].function = NULL;
    }
}

static void load_commands(Command commands[], int command_count) {
    unload_commands(commands, command_count);

    for (int i = 0; i < command_count; i++) {
        commands[i].handle = dlopen(commands[i].library_path, RTLD_LAZY);

        if (commands[i].handle == NULL) {
            printf("Не удалось загрузить %s: %s\n", commands[i].library_path, dlerror());
            continue;
        }

        dlerror();

        commands[i].function = (Operation) dlsym(commands[i].handle, commands[i].function_name);

        const char* error = dlerror();

        if (error != NULL) {
            printf("Не удалось найти функцию %s: %s\n", commands[i].function_name, error);

            dlclose(commands[i].handle);
            commands[i].handle = NULL;
            commands[i].function = NULL;
        }
    }
}

int main(void) {
    Command commands[] = {
        {"Сложение", "./plugins/libadd.so", "add", NULL, NULL},
        {"Вычитание", "./plugins/libsubtract.so", "subtract", NULL, NULL},
        {"Умножение", "./plugins/libmultiply.so", "multiply", NULL, NULL},
        {"Деление", "./plugins/libdivide.so", "divide", NULL, NULL}
    };

    int command_count = (int) (sizeof(commands) / sizeof(commands[0]));
    int choice;
    double first;
    double second;
    double result;

    while (1) {
        load_commands(commands, command_count);
        printf("\n-----------\n");
        printf("\nКалькулятор\n\n");

        int menu_indexes[command_count];
        int available_count = 0;

        for (int i = 0; i < command_count; i++) {
            if (commands[i].function != NULL) {
                menu_indexes[available_count] = i;
                printf("%d. %s\n", available_count + 1, commands[i].name);
                available_count++;
            }
        }

        int refresh_choice = available_count + 1;

        printf("%d. Обновить меню\n", refresh_choice);
        printf("0. Выход\n");
        printf("\nВыберите действие: ");

        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            printf("Ошибка ввода.\n");
            continue;
        }

        if (choice == 0) {
            break;
        }

        if (choice < 1 || choice > refresh_choice) {
            printf("Неизвестная команда.\n");
            continue;
        }

        if (choice == refresh_choice) {
            printf("Меню обновлено.\n");
            continue;
        }

        int command_index = menu_indexes[choice - 1];

        printf("Введите два числа через пробел: ");

        if (scanf("%lf %lf", &first, &second) != 2) {
            clear_input_buffer();
            printf("Ошибка ввода.\n");
            continue;
        }

        if (commands[command_index].function(first, second, &result)) {
            printf("\n-----------\n\n");
            printf("Результат: %g\n", result);
        } else {
            printf("На ноль делить нельзя.\n");
        }
    }

    unload_commands(commands, command_count);

    return 0;
}

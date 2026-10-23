#include <stdio.h>

#include "calc.h"

static void clear_input_buffer(void) {
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
    }
}

typedef struct {
    const char *name;
    Operation function;
} Command;

int main(void) {
    Command commands[] = {
        {"Сложение", add},
        {"Вычитание", subtract},
        {"Умножение", multiply},
        {"Деление", divide}
    };

    int command_count = (int) (sizeof(commands) / sizeof(commands[0]));
    int choice;
    double first;
    double second;
    double result;

    while (1) {
        printf("\n-----------\n");
        printf("\nКалькулятор\n\n");

        for (int i = 0; i < command_count; i++) {
            printf("%d. %s\n", i + 1, commands[i].name);
        }

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

        if (choice < 1 || choice > command_count) {
            printf("Неизвестная команда.\n");
            continue;
        }

        printf("Введите два числа через пробел: ");

        if (scanf("%lf %lf", &first, &second) != 2) {
            clear_input_buffer();
            printf("Ошибка ввода.\n");
            continue;
        }

        if (commands[choice - 1].function(first, second, &result)) {
            printf("\n-----------\n\n");
            printf("Результат: %g\n", result);
        } else {
            printf("На ноль делить нельзя.\n");
        }
    }

    return 0;
}

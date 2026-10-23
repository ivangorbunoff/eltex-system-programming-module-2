#include <stdio.h>

#include "calc.h"

static void clear_input_buffer(void) {
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
    }
}

int main(void) {
    int choice;
    double first;
    double second;
    double result;

    while (1) {
        printf("\n-----------\n");
        printf("\nКалькулятор\n\n");
        printf("1. Сложение\n");
        printf("2. Вычитание\n");
        printf("3. Умножение\n");
        printf("4. Деление\n");
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

        if (choice < 1 || choice > 4) {
            printf("Неизвестная команда.\n");
            continue;
        }

        printf("Введите два числа через пробел: ");

        if (scanf("%lf %lf", &first, &second) != 2) {
            clear_input_buffer();
            printf("Ошибка ввода.\n");
            continue;
        }

        int success = 0;

        switch (choice) {
            case 1:
                success = add(first, second, &result);
                break;
            case 2:
                success = subtract(first, second, &result);
                break;
            case 3:
                success = multiply(first, second, &result);
                break;
            case 4:
                success = divide(first, second, &result);
                break;
        }

        if (success) {
            printf("\n-----------\n\n");
            printf("Результат: %g\n", result);
        } else {
            printf("На ноль делить нельзя.\n");
        }
    }

    return 0;
}

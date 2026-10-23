#include "calc.h"

int add(double first, double second, double *result) {
    *result = first + second;
    return 1;
}

int subtract(double first, double second, double *result) {
    *result = first - second;
    return 1;
}

int multiply(double first, double second, double *result) {
    *result = first * second;
    return 1;
}

int divide(double first, double second, double *result) {
    if (second == 0) {
        return 0;
    }

    *result = first / second;
    return 1;
}

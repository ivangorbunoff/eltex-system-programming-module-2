int divide(double first, double second, double* result) {
    if (second == 0) {
        return 0;
    }

    *result = first / second;

    return 1;
}
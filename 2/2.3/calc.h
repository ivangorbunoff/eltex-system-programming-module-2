#ifndef CALC_H
#define CALC_H

typedef int (*Operation)(double, double, double *);

int add(double first, double second, double *result);
int subtract(double first, double second, double *result);
int multiply(double first, double second, double *result);
int divide(double first, double second, double *result);

#endif

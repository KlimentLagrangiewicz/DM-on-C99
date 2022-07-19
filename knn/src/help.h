
#ifndef HELP_H_
#define HELP_H_

#include <stdio.h>
#include <stdlib.h>

void fscanf_train(double *x, int *y, const int n, const int m, const char *fn);
void fscanf_test(double *x, const int k, const char *fn);
void fprintf_res(const int *y, const int n, const char *fn);
void printf_test(const double *x, const int n, const int m);

#endif

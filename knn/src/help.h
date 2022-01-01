
#ifndef HELP_H_
#define HELP_H_

#include <stdio.h>
#include <stdlib.h>

void fscanf_train(double *x, int *y, const int n, const int m, const char filename[70]);
void fscanf_test(double *x, const int k, const char filename[70]);
void fprintf_res(const int *y, const int n, const char filename[70]);
void printf_test(double *x, int n, int m);

#endif

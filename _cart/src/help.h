
#include <stdio.h>
#include <stdlib.h>

#ifndef HELP_H_
#define HELP_H_

void scanf_train(const char filename[70], double *x, int *y, const int N, const int M);
void scanf_test(const char filename[70], double *x, const int N, const int M);
void printf_res(const char filename[70], const int *y, const int N);

#endif /* HELP_H_ */

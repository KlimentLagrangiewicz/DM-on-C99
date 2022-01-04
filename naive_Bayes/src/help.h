

#ifndef HELP_H_
#define HELP_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int get_num_of_cl(const int *y, const int n);
void fscanf_tr(double *x, int *y, const int n, const int m, const char fn[70]);
void fscanf_ts(double *x, const int n, const char fn[70]);
void fprintf_res(const int *y, const int n, const char fn[70]);

#endif

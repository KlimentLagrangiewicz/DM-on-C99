
#ifndef HELP_H_
#define HELP_H_

#include <stdlib.h>
#include <stdio.h>

void fscanf_data(double *x, const int n, const char filename[70]);
void fprintf_res(const int *y, const int n, const double eps, int min_pts, const char fn[70]);

#endif

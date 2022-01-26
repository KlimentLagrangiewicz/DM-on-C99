
#ifndef KMEANS_H_
#define KMEANS_H_

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <float.h>

double dist_Ev(const double *x, const double *core, const int m, const int l, const int k);
void get_clasters(const double *x, const double *core, int *y, const int n, const int m, const int k);
void calc_centrums(const double *x, const int *y, double *cores, const int n, const int m, const int k);
void start_corenums(int *y, const int k, const int n);
void centrum_mass(const double *x, int k, int m, double *val);
void plusplus(const double *x, double *core, const int n, const int m, const int k);
void kmeans(const double *x, int *res, const int n, const int m, const int k);

#endif

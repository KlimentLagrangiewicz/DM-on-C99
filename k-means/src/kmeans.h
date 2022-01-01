
#ifndef KMEANS_H_
#define KMEANS_H_

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

double dist_Ev(const double *x, const double *core, const int m, const int l, const int k);
int get_claster(const double *x, const double *core, const int m, const int k, const int l);
void get_clasters(const double *x, const double *core, int *y, const int n, const int m, const int k);
void calc_centrum_l(const double *x, double* core, const int *y,const int n, const int m, const int l);
void calc_centrums(const double *x, double *core, const int *y, const int k, const int m);
void start_corenums(int *y, const int k, const int n);
void centrum_mass(const double *x, int k, int m, double *val);
void plusplus(const double *x, double *core, const int n, const int m, const int k);
void kmeans(const double *x, int *res, const int n, const int m, const int k);

#endif


#ifndef DBSCAN_H_
#define DBSCAN_H_

#include <math.h>
#include <string.h>
#include <stdlib.h>

double dist_Ev(const double *x, const int m, const int l, const int k);
void dist_matr(const double *x, double *dists, const int n, const int m);
int n_nums(const double *x, const double *dists, const int n, const int k, const double eps);
void marker(const double *dist, int *status, const int n, const int k, const int marker, const double eps);
void dbscan(const double *x, int *res, const int n, const int m, const int min_pts, const double eps);

#endif

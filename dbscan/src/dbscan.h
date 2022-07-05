
#ifndef DBSCAN_H_
#define DBSCAN_H_

#include <stdlib.h>
#include <math.h>

double distEv(const double *x, const int m, const int l, const int k);
void neighbors_matr(const double *x, short *neighbors, const int n, const int m, const double eps);
int n_nums(const short *neighbors, const int n, const int k, const double eps);
void marker(const short *neighbors, int *status, const int n, const int k, const int mark, const double eps);
void dbscan(const double *x, int *res, const int n, const int m, const int min_pts, const double eps);

#endif


#ifndef KMEANS_H_
#define KMEANS_H_

#include <stdlib.h>
#include <time.h>
#include <float.h>

double distEv(const double *x, const double *core, const int m, const int l, const int k);
int getCluster(const double *x, const double *c, const int l, const int m, const int k);
short calcCores(const double *x, int *y, double *c, const int n, const int m, const int k);
void startCoreNums(int *y, const int k, const int n);
void kmeans(const double *x, int *res, const int n, const int m, const int k);

#endif

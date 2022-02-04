
#ifndef CMEANS_H_
#define CMEANS_H_

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

double gauss(double x, double mx, double sigm) {
	return pow((x - mx) / sigm, 2);
}

double dist_Ev(const double *x, const double *c, const int m, const int l, const int k);
void calc_centrums(const double *x, const double *r, double *c, const int n, const int m, const int k);
double calc_loss(const double *x, const double *r, const double *c, const int n, const int m, const int k);
double norm(double(*f)(double x, double mx, double sigm), double x, double mx, double sigm);
void calc_affiliation(const double *x, const double *c, double *r, const int n, const int m, const int k);
void start_corenums(int *y, const int k, const int n);

#endif

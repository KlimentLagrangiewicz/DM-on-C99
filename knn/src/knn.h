
#ifndef KNN_H_
#define KNN_H_

#include <float.h>
#include <stdlib.h>
#include <math.h>

void sigma(const double *x,const int n,const int m,const int l, double *sig, double *_math);
void z_normalization(double *x, int n, int m);
double dist_Ev(const double *x1, const double *x2, const int m, const int l, const int k);
int getNumOfClass(const int *y, const int n);
void kNN(double *xtrain, const int *y, double *xtest, int *res, const int n, const int m, const int n2, const int k);

#endif

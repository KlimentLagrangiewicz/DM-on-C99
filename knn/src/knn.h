
#ifndef KNN_H_
#define KNN_H_

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

void sigma(const double *x,const int n,const int m,const int l, double *sig, double *_math);
void z_normalization(double *x, int n, int m);
double getdist_Ev(const double *x1, const double *x2, const int m, const int l, const int k);
void get_neighbors(const double *xtrain, const double *xtest, int *y, const int n, const int m, const int k, const int num);
void get_classneighbors(const int *y, int *nei,const int num);
int get_num_class(const int *nei, const int num);
int get_class_forl(const double *xtrain, const int *y, const double *xtest, const int n, const int m, const int k, const int l);
void kNN(const double *xtrain, const int *y, const double *xtest, int *res, const int n,const int m, const int n2, const int k);

#endif

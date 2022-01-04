

#ifndef NAIVE_BAYES_H_
#define NAIVE_BAYES_H_

void pr_one(const double x, const double *xlearn, const int *C, const int n, const int m, const int k, const int c, double *pc, double *pxc, double *px);
double pr_cx(const double x, const double *xtrain, const int *C, const int c, const int n, const int m, const int k);
double pr_cX(const double *x, const double *xtrain, const int *C, const int c, const int n, const int m, const int j);
int numofclass(const double *x, const double *xtrain, const int *C, const int kl, const int n, const int m, const int j);
void bayes(const double *xtest, const double *xtrain, const int *C, const int kl, const int n, const int m, const int n2, int *res);

#endif

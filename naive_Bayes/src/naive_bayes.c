#include "naive_bayes.h"

void pr_one(const double x, const double *xlearn, const int *C, const int n, const int m, const int k, const int c, double *pc, double *pxc, double *px) {
	int num_c, num_xc, num_x;
	num_c = num_xc = num_x = 0;
	for (int i = 0; i < n; i++){
		if (C[i] == c)
			num_c++;
		if (xlearn[i * m + k] == x) {
			num_x++;
			if (C[i] == c)
				num_xc++;
		}
	}
	*pc = (double)num_c/n;
	*pxc = (double)num_xc/num_x;
	*px = (double)num_xc/n;
}

double pr_cx(const double x, const double *xtrain, const int *C, const int c, const int n, const int m, const int k) {
	double pxc, px, pc;
	pr_one(x, xtrain, C, n, m,  k, c, &pc, &pxc, &px);
    return (px == 0)?0.0:(pc*pxc/px);
}

double pr_cX(const double *x, const double *xtrain, const int *C, const int c, const int n, const int m, const int j) {
	double pr = 1.0;	;
	for (int i = 0; i < m; i++)
		pr *= pr_cx(x[j * m + i], xtrain, C, c, n, m, i);
	return pr;
}

int numofclass(const double *x, const double *xtrain, const int *C, const int kl, const int n, const int m, const int j) {
	double pr = pr_cX(x, xtrain, C, 0, n, m, j);
	int kmax = 0;
	for (int i = 0; i < kl; i++){
		double cur = pr_cX(x, xtrain, C, i, n, m, j);
		if (cur > pr){
			pr = cur;
			kmax = i;
		}
	}
	return kmax;
}

void bayes(const double *xtest, const double *xtrain, const int *C, const int kl, const int n, const int m, const int n2, int *res) {
	for (int i = 0; i < n2; i++)
		res[i] = numofclass(xtest, xtrain, C, kl, n, m, i);
}

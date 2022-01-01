#include "knn.h"

void sigma(const double *x,const int n,const int m,const int l, double *sig, double *_math) {
	double sigma = 0.0;
	double av = 0.0;
	for (int i = 0; i < n; i++)
		av += x[i * m + l];
	av = av/(double)n;
	for (int i = 0; i < n; i++)
		sigma += pow((x[i * m + l] - av), 2.0);
	sigma = sqrt(sigma/(double)n);
	*sig = sigma;
	*_math = av;
}

void z_normalization(double *x, const int n, const int m) {
	double *av =(double*)malloc(m * sizeof(double));
	double *sigm = (double*)malloc(m *sizeof(double));
	for (int i = 0; i < m; i++)
		sigma(x, n, m, i, &sigm[i], &av[i]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			x[i * m + j] = (x[i * m + j] - av[j])/sigm[j];
	free(av);
	free(sigm);
}

double getdist_Ev(const double *x1, const double *x2, const int m, const int l, const int k) {
	double dist = 0.0;
	for (int i = 0; i < m; i++)
		dist += pow((x1[l * m + i] - x2[k * m + i]), 2.0);
	return sqrt(dist);
}

void get_neighbors(const double *xtrain, const double *xtest, int *y, const int n, const int m, const int k, const int num) {
	bool *vect = (bool*)malloc(n * sizeof(bool));
	memset(vect, 1, n * sizeof(bool));
	for (int i = 0; i < num; i++) {
		int kmin = 0;
		while (!vect[kmin]) {
			kmin++;
		}
		double dist_min = getdist_Ev(xtrain, xtest, m, kmin, k);
		for (int j = kmin; j < n; j++) {
			if (vect[j]) {
				double cur_dist = getdist_Ev(xtrain, xtest, m, j, k);
				if (cur_dist < dist_min) {
					dist_min = cur_dist;
					kmin = j;
				}
			}
		}
		vect[kmin] = false;
		y[i] = kmin;
	}
	free(vect);
}

void get_classneighbors(const int *y, int *nei,const int num) {
	for (int i = 0; i < num; i++)
		nei[i] = y[nei[i]];
}

int get_num_class(const int *nei, const int num) {
	int *freg = (int*)calloc(num, sizeof(int));
	for (int i = 0; i < num; i++)
		for (int j = i; j < num; j++)
			if (nei[i] == nei[j])
				freg[i]++;
	int max = freg[0];
	int k_max = 0;
	for (int i = 0; i < num; i++)
		if (freg[i] > max) {
			max = freg[i];
			k_max = i;
		}
	free(freg);
	return nei[k_max];
}

int get_class_forl(const double *xtrain, const int *y, const double *xtest, const int n, const int m, const int k, const int l) {
	int *neig = (int*)malloc(k * sizeof(int));
	get_neighbors(xtrain, xtest, neig, n, m, l, k);
	get_classneighbors(y, neig, k);
	int f = get_num_class(neig, k);
	free(neig);
	return f;
}

void kNN(const double *xtrain, const int *y, const double *xtest, int *res, const int n, const int m, const int n2, const int k) {
	for (int i = 0; i < n2; i++)
		res[i] = get_class_forl(xtrain, y, xtest, n, m, k, i);
}

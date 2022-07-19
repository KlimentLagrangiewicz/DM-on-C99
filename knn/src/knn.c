#include "knn.h"

void z_normalization(double *x, const int n, const int m) {
	double mean, d, disp;
	int i, j;
	const int b = n * m;
	for (j = 0; j < m; j++) {
		mean = disp = 0;
		for (i = j; i < b; i += m) {
			mean += x[i] / (double)n;
		}
		for (i = j; i < b; i += m) {
			d = x[i] - mean;
			disp += d * d / (double)n;
		}
		disp = sqrt(disp);
		for (i = j; i < b; i += m) {
			x[i] = (x[i] - mean) / disp;
		}
	}
}

double dist_Ev(const double *x1, const double *x2, const int m, const int l, const int k) {
	int i;
	double d, dist = 0;
	for (i = 0; i < m; i++) {
		d = x1[l + i] - x2[k + i];
		dist += d * d;
	}
	return dist;
}

int getNumOfClass(const int *y, const int n) {
	int i, j, cur;
	short *v = (short*)malloc(n * sizeof(short));
	for (i = 0; i < n; i++) {
		v[i] = 0;
	}
	for (i = 0; i < n; i++) {
		while ((v[i]) && (i < n)) i++;
		cur = y[i];
		for (j = i + 1; j < n; j++) {
			if (y[j] == cur)
				v[j] = 1;
		}
	}
	cur = 0;
	for (i = 0; i < n; i++) {
		if (v[i] == 0) cur++;
	}
	free(v);
	return cur;
}

void kNN(double *xtrain, const int *y, double *xtest, int *res, const int n, const int m, const int n2, const int k) {
	z_normalization(xtrain, n ,m);
	z_normalization(xtest, n2, m);
	int i, j, l, id, noc = getNumOfClass(y, n);
	double min_d, cur_d;
	int *r = (int*)malloc(noc * sizeof(int));
	short *v = (short*)malloc(n * sizeof(short));
	for (i = 0; i < n2; i++) {
		for (j = 0; (j < n) && (j < noc); j++) {
			v[j] = 0;
			r[j] = 0;
		}
		if (noc > n) {
			for (j = n; j < noc; j++) {
				r[i] = 0;
			}
		}
		if (n > noc) {
			for (j = noc; j < n; j++) {
				v[j] = 0;
			}
		}
		for (j = 0; j < k; j++) {
			l = 0;
			while (v[l]) l++;
			min_d = DBL_MAX;
			id = l;
			for (; l < n; l++) {
				if (v[l] == 0) {
					cur_d = dist_Ev(xtest, xtrain, m, i * m, l * m);
					if (cur_d < min_d) {
						min_d = cur_d;
						id = l;
					}
				}
			}
			v[id] = 1;
			r[y[id]]++;
		}
		id = 0;
		l = 0;
		for (j = 0; j < noc; j++) {
			if (r[j] > l) {
				l = r[j];
				id = j;
			}
		}
		res[i] = id;
	}
	free(r);
	free(v);
}

#include "dbscan.h"

double dist_Ev(const double *x, const int m, const int l, const int k) {
	double dist = 0.0;
	for (int i = 0; i < m; i++)
		dist += pow(x[l * m + i] - x[k * m + i], 2.0);
	return sqrt(dist);
}

void dist_matr(const double *x, double *dists, const int n, const int m) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if(i != j)
				dists[i * n + j] = dist_Ev(x, m, i, j);
			else dists[i * n + j] = 0.0;
}

int n_nums(const double *x, const double *dists, const int n, const int k, const double eps) {
	int num = 0;
	for (int i = 0; i < n; i++)
		if ((dists[k * n + i] < eps) && (i != k))
			num++;
	return num;
}

void marker(const double *dist, int *status, const int n, const int k, const int mark, const double eps) {
	for (int i = 0; i < n; i++) {
		if ((status[i] == -1) && (dist[i * n + k] < eps) && (i != k)) {
			status[i] = mark;
			marker(dist, status, n, i, mark, eps);
		}
	}
}

void dbscan(const double *x, int *res, const int n, const int m, const int min_pts, const double eps) {
	memset(res, -1, n * sizeof(int));
	double *dist = (double*)malloc(n * n * sizeof(double));
	dist_matr(x, dist, n, m);
	int count = 0;
	for (int i = 0; i < n; i++) {
		if ((res[i] == -1) && (n_nums(x, dist, n , i, eps) > min_pts)) {
			res[i] = count;
			marker(dist, res, n, i, count, eps);
			count++;
		}
	}
	free(dist);
	for (int i = 0; i < n; i++)
		if (res[i] == -1)
			res[i] = -2;
}

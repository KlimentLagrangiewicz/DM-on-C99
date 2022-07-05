#include "dbscan.h"

double distEv(const double *x, const int m, const int l, const int k) {
	double d, dist = 0;
	int i;
	for (i = 0; i < m; i++) {
		d = x[l + i] - x[k + i];
		dist += d * d;
	}
	return sqrt(dist);
}

void neighbors_matr(const double *x, short *neighbors, const int n, const int m, const double eps) {
	int i, id1, id2;
	for (i = 0; i < n * n; i++) {
		id1 = i / n;
		id2 = i - id1 * n;
		neighbors[i] = ((distEv(x, m, id1 * m, id2 * m) <= eps) && (id1 != id2)) ? 1 : 0;
	}
}

int n_nums(const short *neighbors, const int n, const int k, const double eps) {
	int i, num = 0;
	for (i = 0; i < n; i++)
		if (neighbors[k * n + i])
			num++;
	return num;
}

void marker(const short *neighbors, int *status, const int n, const int k, const int mark, const double eps) {
	int i;
	for (i = 0; i < n; i++) {
		if ((status[i] == -1) && (neighbors[k * n + i])) {
			status[i] = mark;
			marker(neighbors, status, n, i, mark, eps);
		}
	}
}

void dbscan(const double *x, int *res, const int n, const int m, const int min_pts, const double eps) {
	int i, count = 0;
	for (i = 0; i < n; i++) {
		res[i] = -1;
	}
	short *neighbors = (short*)malloc(n * n * sizeof(short));
	neighbors_matr(x, neighbors, n, m, eps);
	for (i = 0; i < n; i++) {
		if ((res[i] == -1) && (n_nums(neighbors, n, i, eps) >= min_pts)) {
			res[i] = count;
			marker(neighbors, res, n, i, count, eps);
			count++;
		}
	}
	free(neighbors);
	for (i = 0; i < n; i++)
		if (res[i] == -1)
			res[i] = -2;
}

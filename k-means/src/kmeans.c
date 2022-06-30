#include "kmeans.h"

double distEv(const double *x, const double *core, const int m, const int l, const int k) {
	double d, dist = 0;
	int i;
	const int buf1 = l * m, buf2 = k * m;
	for (i = 0; i < m; i++) {
		d = x[buf1 + i] - core[buf2 + i];
		dist += d * d;
	}
	return dist;
}

int getCluster(const double *x, const double *c, const int l, const int m, const int k) {
	int i, res = 0;
	double cur, dis = DBL_MAX;
	for (i = 0; i < k; i++) {
		cur = distEv(x, c, m, l, i);
		if (cur < dis) {
			dis = cur;
			res = i;
		}
	}
	return res;
}

short calcCores(const double *x, int *y, double *c, const int n, const int m, const int k) {
	int *nums = (int*)malloc(k * sizeof(int));
	double *nc = (double*)malloc(k * m * sizeof(double));
	int i, j ,f, buf1, buf2, r = 0;
	for (i = 0 ; i < k; i++) {
		nums[i] = 0;
		nc[i] = 0;
	}
	for (i = k - 1; i < k * m; i++) {
		nc[i] = 0;
	}
	for (i = 0; i < n; i++) {
		f = getCluster(x, c, i, m, k);
		nums[f]++;
		if (f == y[i]) r++;
		y[i] = f;
		buf1 = f * m;
		buf2 = i * m;
		for (j = 0; j < m; j++) {
			nc[buf1 + j] += x[buf2 + j];
		}
	}
	for (i = 0; i < k * m; i++) {
		c[i] = nc[i] / nums[i / m];
	}
	free(nc);
	free(nums);
	return (r == n) ? 0 : 1;
}

static short constr(int *y, int val, int s) {
	short flag = 1;
	int i;
	for (i = 0; i < s && (flag == 1); i++) {
		if (y[i] == val) flag = 0;
	}
	return flag;
}

void startCoreNums(int *y, const int k, const int n) {
	srand(time(NULL));
	int i;
	for (i = 0; i < k; i++) {
		int val;
		do {
			val = rand() % n;
		} while (constr(y, val, i) == 0);
		y[i] = val;
	}
}

void kmeans(const double *x, int *res, const int n, const int m, const int k) {
	short flag = 1;
	double *cores = (double*)malloc(k * m * sizeof(double));
	int *start_num = (int*)malloc(k * sizeof(int));
	startCoreNums(start_num, k, n);
	int i;
	for (i = 0; i < k * m; i++) {
		cores[i] = x[start_num[i / m] * m + i - (i / m) * m];
	}
	free(start_num);
	do {
		flag = calcCores(x, res, cores, n, m, k);
	} while (flag != 0);
	free(cores);
}

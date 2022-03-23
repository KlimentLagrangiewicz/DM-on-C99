#include "kmeans.h"

double dist_Ev(const double *x, const double *core, const int m, const int l, const int k) {
	double dist = 0;
	int i;
	const int buf1 = l * m, buf2 = k * m;
	for (i = 0; i < m; i++)
		dist += pow(x[buf1 + i] - core[buf2 + i], 2.0);
	return sqrt(dist);
}

short get_clasters(const double *x, const double *core, int *y, const int n, const int m, const int k) {
	int i, j, f = 0;
	for (i = 0; i < n; i++) {
		int claster = 0;
		double dist = DBL_MAX;
		for (j = 0; j < k; j++) {
			double cur_dist = dist_Ev(x, core, m, i, j);
			if (cur_dist < dist) {
				dist = cur_dist;
				claster = j;
			}
		}
		if (y[i] == claster) f++;
		y[i] = claster;
	}
	return (f == n) ? 0 : 1;
}

void calc_centrums(const double *x, const int *y, double *cores, const int n, const int m, const int k) {
	memset(cores, 0,  m * k * sizeof(double));
	int *nums = (int*)malloc(k * sizeof(int));
	memset(nums, 0, k * sizeof(int));
	int i, j;
	for (i = 0; i < n; i++) {
		int buf = y[i];
		for (j = 0; j < m; j++) {
			cores[buf * m + j] += x[i * m + j];
		}
		nums[buf]++;
	}
	for (i = 0; i < k; i++) {
		int buf = nums[i];
		for (j = 0; j < m; j++)
			cores[i * m + j] /= buf;
	}
	free(nums);
}

static short constr(int *y, int val, int s) {
	short flag = 1;
	int i;
	for (i = 0; i < s && (flag == 1); i++) {
		if (y[i] == val) flag = 0;
	}
	return flag;
}

void start_corenums(int *y, const int k, const int n) {
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
	double *core = (double*)malloc(k * m * sizeof(double));
	int *start_num = (int*)malloc(k * sizeof(int));
	start_corenums(start_num, k, n);
	int i;
	for (i = 0; i < k; i++)
		memcpy(&core[i * m], &x[start_num[i] * m], m * sizeof(double));
	free(start_num);
	get_clasters(x, core, res, n, m, k);
	do {
		calc_centrums(x, res, core, n, m, k);
		flag = get_clasters(x, core, res, n, m, k);
	} while (flag != 0);
	free(core);
}

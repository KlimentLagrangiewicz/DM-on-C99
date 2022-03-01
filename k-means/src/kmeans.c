#include "kmeans.h"

double dist_Ev(const double *x, const double *core, const int m, const int l, const int k) {
	double dist = 0;
	for (int i = 0; i < m; i++)
		dist += pow(x[l * m + i] - core[k * m + i], 2.0);
	return dist;
}

void get_clasters(const double *x, const double *core, int *y, const int n, const int m, const int k) {
	double *min_dist = (double*)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++) {
		min_dist[i] = DBL_MAX;
	}
	memset(y, 0, n * sizeof(int));
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++) {
			double cur_dist = dist_Ev(x, core, m, j, i);
			if (cur_dist < min_dist[j]) {
				min_dist[j] = cur_dist;
				y[j] = i;
			}
		}
	}
	free(min_dist);
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
	short flag = -1;
	int i;
	for (i = 0; i < s && (flag == -1); i++) {
		if (y[i] == val) flag = 0;
	}
	return flag;
}

void start_corenums(int *y, const int k, const int n) {
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
	bool flag = false;
	double *core = (double*)malloc(k * m * sizeof(double));
	int *start_num = (int*)malloc(k * sizeof(int));
	start_corenums(start_num, k, n);
	for (int i = 0; i < k; i++)
		memcpy(&core[i * m], &x[start_num[i] * m], m * sizeof(double));
	free(start_num);
	int *new_res = (int*)malloc(n * sizeof(int));
	get_clasters(x, core, res, n, m, k);
	do {
		calc_centrums(x, res, core, n, m, k);
		get_clasters(x, core, new_res, n, m, k);
		flag = memcmp(res, new_res, n * sizeof(int));
	    memcpy(res, new_res, n * sizeof(int));
	} while (flag);
	free(core);
	free(new_res);
}

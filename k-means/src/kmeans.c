#include "kmeans.h"

double dist_Ev(const double *x, const double *core, const int m, const int l, const int k) {
	double dist = 0.0;
	for (int i = 0; i < m; i++)
		dist += pow(x[l * m + i] - core[k * m + i], 2.0);
	return dist;
}

int get_claster(const double *x, const double *core, const int m, const int k, const int l) {
	int kmin = 0;
	double min_dist = dist_Ev(x, core, m, l, 0);
	for (int i = 0; i < k; i++) {
		double cur_dist = dist_Ev(x, core, m, l, i);
		if (cur_dist < min_dist) {
			min_dist = cur_dist;
			kmin = i;
		}
	}
	return kmin;
}

void get_clasters(const double *x, const double *core, int *y, const int n, const int m, const int k) {
	for (int i = 0; i < n; i++)
		y[i] = get_claster(x, core, m, k, i);
}

void calc_centrums(const double *x, const int *y, double *cores, const int n, const int m, const int k) {
	memset(cores, 0,  m * k * sizeof(double));
	int *nums = (int*)malloc(k * sizeof(int));
	memset(nums, 0, k * sizeof(int));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cores[y[i] * m + j] += x[i * m + j];
		}
		nums[y[i]]++;
	}
	for (int i = 0; i < k; i++)
		for (int j = 0; j < m; j++)
			cores[i * m + j] /= nums[i];
	free(nums);
}

void start_corenums(int *y, const int k, const int n) {
	srand(time(NULL));
    for (int i = 0; i < k; i++) {
        if (i == 0) y[i] = rand() % n;
        else {
            int val;
            do {
                val = rand() % n;
            } while(memchr(y, val, i * sizeof(int)) != NULL);
            y[i] = val;
        }
    }
}

void centrum_mass(const double *x, int k, int m, double *val) {
	memset(val, 0.0, m * sizeof(double));
	for (int i = 0; i < m; i++) {
		double sum = 0.0;
		for (int j = 0; j < k; j++)
			sum += x[j * m + i];
		val[i] = sum / k;
	}
}

void plusplus(const double *x, double *core, const int n, const int m, const int k) {
	double *cur_ = (double*)malloc(m * sizeof(double));
	bool *vect = (bool*)malloc(n * sizeof(bool));
	memset(vect, 1, n * sizeof(bool));
	for (int i = 0; i < k; i++) {
		int cur = 0;
		if (i == 0) {
			centrum_mass(x, n, m, cur_);
			double max_dist = dist_Ev(x, cur_, m, 0, 0);
			for (int i = 0; i < n; i++) {
				double cur_dist = dist_Ev(x, cur_, m, i, 0);
				if (cur_dist > max_dist) {
					cur = i;
					max_dist = cur_dist;
				}
			}
		} else {
			while (!vect[cur]) {
				cur++;
			}
			centrum_mass(core, i, m, cur_);
			double max_dist = dist_Ev(x, cur_, m, cur, 0);
			int f = cur;
			for (int j = f; j < n; j++)
				if (vect[j]) {
					double cur_dist =  dist_Ev(x, cur_, m, j, 0);
					if (cur_dist > max_dist) {
						max_dist = cur_dist;
						cur = j;
					}
				}
		}
		memcpy(&core[i * m], &x[cur * m], m * sizeof(double));
		vect[cur] = false;
	}
	free(cur_);
	free(vect);
}

void kmeans(const double *x, int *res, const int n, const int m, const int k) {
	bool flag = false;
	double *core = (double*)malloc(k * m * sizeof(double));
	//plusplus(x, core, n, m, k);
	int *start_num = (int*)malloc(k * sizeof(int));
	start_corenums(start_num, k, n);
	for (int i = 0; i < k; i++)
		memcpy(&core[i * m], &x[start_num[i] * m], m * sizeof(double));
	free(start_num);
	printf("Ядра:\n");
	for (int i = 0; i < k; i++){
		for (int j = 0; j < m; j++)
			printf(" %.2lf ", core[i * m + j]);
		printf("\n");
	}
	int *new_res = (int*)malloc(n * sizeof(int));
	get_clasters(x, core, res, n, m, k);
	do {
		calc_centrums(x, res, core, n, m, k);
		get_clasters(x, core, new_res, n, m, k);
		flag = memcmp(res, new_res, n * sizeof(int));
	    memcpy(res, new_res, n * sizeof(int));
	} while(flag);
	free(core);
	free(new_res);
}

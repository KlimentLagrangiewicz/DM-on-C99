#include "cmeans.h"

double dist_Ev(const double *x, const double *c, const int m, const int l, const int k) {
	volatile double sum = 0;
	for (int i = 0; i < m; i++)
		sum += pow(x[l * m + i] - c[k * m + i], 2.0);
	return sqrt(sum);
}

void calc_centrums(const double *x, const double *r, double *c, const int n, const int m, const int k) {
	for (int i = 0; i < k; i++) {
		for (int l = 0; l < m; l++) {
			volatile double sum1 = 0, sum2 = 0;
			for (int j = 0; j < n; j++) {
				sum1 += r[j * k + i] * x[j * m + l];
				sum2 += r[j * k + i];
			}
			c[i * m + l] = sum1 / sum2;
		}
	}
}

double calc_loss(const double *x, const double *r, const double *c, const int n, const int m, const int k) {
	volatile double sum = 0;
	for (int i = 0; i < k; i++)
		for (int j = 0; j < n; j++)
			sum += pow(dist_Ev(x, c, m, j, i), 2.0) * r[j * k + i];
	return sum;
}

double norm(double(*f)(double x, double mx, double sigm), double x, double mx, double sigm) {
	double sum = 0;
	double h = (x - (FLT_MIN / 2.0)) / SHRT_MAX;
	for (double xi = FLT_MIN / 2.0; xi < x; xi += h) {
		sum += (f(xi, mx, sigm) + 3 * f(xi + h / 3, mx, sigm) + 3 * f(xi + 2 * h / 3, mx, sigm) + f(xi + h, mx, sigm)) / 8.0;
	}
	return sum / (sqrt(2 * M_PI) * sigm);
}

void calc_affiliation(const double *x, const double *c, double *r, const int n, const int m, const int k) {
	double *norm_ = (double*)malloc(n * k * sizeof(double));
	double *sum = (double*)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++) {
		double buff = 0;
		for (int j = 0; j < k; j++) {
			norm_[i * k + j] = norm(gauss, dist_Ev(x, c, m, i, j), 0, 1);
			buff += norm_[i * k + j];
		}
		sum[i] = buff;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			r[i * k + j] = norm_[i * k + j] / sum[i];
		}
	}
	free(norm_);
	free(sum);
}

void start_corenums(int *c, const int k, const int n) {
	srand(time(NULL));
    for (int i = 0; i < k; i++) {
        if (i == 0) c[i] = rand() % n;
        else {
            int val;
            do {
                val = rand() % n;
            } while(memchr(c, val, i * sizeof(int)) != NULL);
            c[i] = val;
        }
    }
}

void cmeans(const double *x, double *r, const int n, const int m, const int k) {
	double *c = (double *)malloc(k * m * sizeof(double));
	int *y = (int*)malloc(k * sizeof(int));
	start_corenums(y, k, n);
	for (int i = 0; i < k; i++) {
		memcpy(&c[i * m], &x[y[i] * m], m * sizeof(double));
	}
	free(y);
	double old = DBL_MAX, new;
	bool flag = true;
	do {
		calc_affiliation(x, c, r, n, m ,k);
		calc_centrums(x, r, c, n, m, k);
		new = calc_loss(x, r, c, n, m, k);
		flag = (new - old < 0)?true:false;
		old = new;
	} while (flag);
	free(c);
}

#include "help.h"

void fscanf_train(double *x, int *y, const int n, const int m, const char fn[]) {
	FILE *file;
	if ((file = fopen(fn, "r")) == NULL) {
		printf("Error in opening %s training file\n", fn);
		exit(1);
	}
	int i, j;
	for (i = 0; i < n && !feof(file); i++) {
		for (j = 0; j < m && !feof(file); j++)
			if (fscanf(file, "%lf", &x[i * m + j]) == 0) {}
		if (!feof(file)) if (fscanf(file, "%d", &y[i]) == 0) {}
	}
	fclose(file);
}

void fscanf_test(double *x, const int k, const char fn[]) {
	FILE *file;
	if ((file = fopen(fn, "r")) == NULL) {
		printf("Error in opening %s file\n", fn);
		exit(1);
	}
	int i;
	for (i = 0; i < k && !feof(file); i++)
		if (fscanf(file, "%lf", &x[i]) == 0) {}
	fclose(file);
}

void fprintf_res(const int *y, const int n, const char fn[]) {
	FILE *file;
	if ((file = fopen(fn, "a")) == NULL) {
		printf("Error in opening %s result file\n", fn);
		exit(1);
	}
	int i;
	fprintf(file, "Result of k-NN classification...\n");
	for (i = 0; i < n; i++)
		fprintf(file, "Object[%d]: %d;\n", i, y[i]);
	fclose(file);
}

void printf_test(const double *x, const int n, const int m) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++)
			printf(" %.2lf ", x[i * m + j]);
		printf("\n");
	}
}

#include "help.h"

void fscanf_train(double *x, int *y, const int n, const int m, const char filename[70]) {
	FILE *file;
	if ((file = fopen(filename, "r")) == NULL) {
		printf("Error in opening train file\n");
		exit(1);
	}
	for (int i = 0; i < n && !feof(file); i++) {
		for (int j = 0; j < m && !feof(file); j++)
			fscanf(file, "%lf", &x[i * m + j]);
		if (!feof(file)) fscanf(file, "%d", &y[i]);
	}
	fclose(file);
}

void fscanf_test(double *x, const int k, const char filename[70]) {
	FILE *file;
	if ((file = fopen(filename, "r")) == NULL) {
		printf("Error in opening test file\n");
		exit(1);
	}
	for (int i = 0; i < k && !feof(file); i++)
		fscanf(file, "%lf", &x[i]);
	fclose(file);
}

void fprintf_res(const int *y, const int n, const char filename[70]) {
	FILE *file;
	if ((file = fopen(filename, "a")) == NULL) {
		printf("Error in opening result file\n");
		exit(1);
	}
	fprintf(file, "Результат классификации kNN...\n");
	for (int i = 0; i < n; i++)
		fprintf(file, "Объект: %d; Класс: %d;\n", i, y[i]);
	fclose(file);
}

void printf_test(double *x, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			printf(" %.2lf ", x[i * m + j]);
		printf("\n");
	}
}

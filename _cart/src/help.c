#include "help.h"

void scanf_train(const char filename[70], double *x, int *y, const int N, const int M) {
	FILE *file;
	if ((file = fopen(filename, "r")) == NULL) {
		printf("Error in opening train file\n");
		exit(1);
	}
	for (int i = 0; i < N && !feof(file); i++) {
		for (int j = 0; j < M && !feof(file); j++) {
			fscanf(file, "%lf", &x[i * M + j]);
		}
		if (!feof(file))
			fscanf(file, "%d", &y[i]);
	}
	fclose(file);
}

void scanf_test(const char filename[70], double *x, const int N, const int M) {
	FILE *file;
	if ((file = fopen(filename, "r")) == NULL) {
		printf("Error in opening test file\n");
		exit(1);
	}
	for (int i = 0; i < N * M && !feof(file); i++)
		fscanf(file, "%lf", &x[i]);
	fclose(file);
}

void printf_res(const char filename[70], const int *y, const int N) {
	FILE *file;
	if ((file = fopen(filename, "a")) == NULL) {
		printf("Error in opening result file\n");
		exit(1);
	}
	fprintf(file, "Результат классификации CART...\n");
	for (int i = 0; i < N; i++)
		fprintf(file, "Объект: %d Класс: %d\n", i, y[i]);
	fclose(file);
}

int get_num_of_cl(const int *y, const int n) {
	int nums = 0;
	bool *vect = (bool*)malloc(n * sizeof(bool));
	memset(vect, 1, n * sizeof(bool));
	for (int i = 0; i < n; i++)
		for (int j = i; j < n && vect[i]; j++)
			if ((j != i) && (y[i] == y[j]))
				vect[j] = false;
	for (int i = 0; i < n; i++)
		if (vect[i])
			nums++;
	free(vect);
	return nums;
}

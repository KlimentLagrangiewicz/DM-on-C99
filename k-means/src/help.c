#include "help.h"

void fscanf_data(double *x, const int n, const char filename[70]) {
	FILE *file;
	if ((file = fopen(filename, "r")) == NULL) {
		printf("Error in opening data file..\n");
		exit(1);
	}
	for (int i = 0; i < n && !feof(file); i++)
		if (fscanf(file, "%lf", &x[i]) == 0) {}
	fclose(file);
}

void fprintf_res(const int *y, const int n, const char filename[70]) {
	FILE *file;
	if ((file = fopen(filename, "a")) == NULL) {
		printf("Error in opening result file...\n");
		exit(1);
	}
	fprintf(file, "Результат кластеризации k-means...\n");
	for (int i = 0; i < n; i++)
		fprintf(file, "Объект: %d; Кластер: %d;\n", i, y[i]);
	fclose(file);
}

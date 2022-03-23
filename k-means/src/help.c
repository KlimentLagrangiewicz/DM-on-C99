#include "help.h"

void fscanf_data(double *x, const int n, const char fn[]) {
	FILE *file;
	if ((file = fopen(fn, "r")) == NULL) {
		printf("Error in opening %s file..\n", fn);
		exit(1);
	}
	int i;
	for (i = 0; i < n && !feof(file); i++)
		if (fscanf(file, "%lf", &x[i]) == 0) {}
	fclose(file);
}

void fprintf_res(const int *y, const int n, const char fn[]) {
	FILE *file;
	if ((file = fopen(fn, "a")) == NULL) {
		printf("Error in opening %s file...\n", fn);
		exit(1);
	}
	int i;
	fprintf(file, "Результат кластеризации k-means...\n");
	for (i = 0; i < n; i++)
		fprintf(file, "Объект: %d; Кластер: %d;\n", i, y[i]);
	fclose(file);
}

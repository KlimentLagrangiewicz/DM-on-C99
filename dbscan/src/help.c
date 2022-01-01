#include "help.h"

void fscanf_data(double *x, const int n, const char filename[70]) {
	FILE *file;
	if ((file = fopen(filename, "r")) == NULL) {
		printf("Error in opening data file...\n");
		exit(1);
	}
	for (int i = 0; i < n && !feof(file); i++)
		if (fscanf(file, "%lf", &x[i]) == 0) {}
	fclose(file);
}

void fprintf_res(const int *y, const int n, const double eps, const int min_pts, const char fn[70]) {
	FILE *file;
	if ((file = fopen(fn, "a")) == NULL) {
		printf("Error in opening result file...\n");
		exit(1);
	}
	fprintf(file, "Результат кластеризации DBSCAN...\n");
	fprintf(file, "Параметры: eps: %.2lf, min_pts: %d\n", eps, min_pts);
	for (int i = 0; i < n; i++)
		if (y[i] == -2)
			fprintf(file, "Объект: %d; Шум;\n", i);
		else
			fprintf(file, "Объект: %d; Кластер: %d;\n", i, y[i]);
	fclose(file);
}

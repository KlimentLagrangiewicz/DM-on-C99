#include "help.h"

void fscanf_data(double *x, const int n, const char fn[]) {
	FILE *file;
	if ((file = fopen(fn, "r")) == NULL) {
		printf("Error in %s file...\n", fn);
		exit(1);
	}
	int i;
	for (i = 0; i < n && !feof(file); i++)
		if (fscanf(file, "%lf", &x[i]) == 0) {}
	fclose(file);
}

void fprintf_res(const int *y, const int n, const double eps, const int min_pts, const char fn[]) {
	FILE *file;
	if ((file = fopen(fn, "a")) == NULL) {
		printf("Error in opening result file...\n");
		exit(1);
	}
	fprintf(file, "Result of DBSCAN clustering...\n");
	fprintf(file, "Eps: %.2lf, min_pts: %d\n", eps, min_pts);
	int i;
	for (i = 0; i < n; i++)
		if (y[i] == -2)
			fprintf(file, "Object[%d]: Noise;\n", i);
		else
			fprintf(file, "Object[%d]: Cluster %d;\n", i, y[i]);
	fclose(file);
}

#include "help.h"

void fscanf_data(double *x, const int m, char fn[70]) {
	FILE *file;
	if ((file = fopen(fn, "r")) == NULL) {
		printf("Error in opening data file\n");
		exit(1);
	}
	for (int i = 0; i < m && !feof(file); i++)
		if (fscanf(file, "%lf", &x[i]) == 0) {}
	fclose(file);
}

void fprintf_data(const double *r, const int n, const int k, char fn[70]){
	FILE *file;
	if ((file = fopen(fn, "a")) == NULL) {
		printf("\n");
		exit(1);
	}
	fprintf(file, "Результат классификации c-means...\n");
	for (int i = 0; i < n; i++) {
		fprintf(file, "Объект: %d;", i);
		for (int j = 0; j < k; j++)
			fprintf(file, " %.4lf", r[i * k + j]);
		fprintf(file, "\n");
	}
	fclose(file);
}



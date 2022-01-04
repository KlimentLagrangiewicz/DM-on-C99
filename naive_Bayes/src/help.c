#include "help.h"

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


void fscanf_tr(double *x, int *y, const int n, const int m, const char fn[70]) {
	FILE *file;
	if((file = fopen(fn, "r")) == NULL) {
		printf("Error in opening training file\n");
		exit(1);
	}
	for (int i = 0; i < n && !feof(file); i++) {
		for (int j = 0; j < m && !feof(file); j++) {
			if (fscanf(file, "%lf", &x[i * m + j]) == 0) {}
		}
		if (!feof(file)) if (fscanf(file, "%d", &y[i]) == 0) {}
	}
	fclose(file);
}

void fscanf_ts(double *x, const int n, const char fn[70]) {
	FILE *file;
	if ((file = fopen(fn, "r")) == NULL) {
		printf("Error in opening test file\n");
		exit(1);
	}
	for (int i = 0; i < n && !feof(file); i++)
		if (fscanf(file, "%lf", &x[i]) == 0) {}
	fclose(file);
}

void fprintf_res(const int *y, const int n, const char fn[70]) {
	FILE *file;
	if ((file = fopen(fn, "a")) == NULL) {
		printf("Error opening result file\n");
		exit(1);
	}
	fprintf(file, "Результат классификации наивным байесовским классификатором...\n");
	for (int i = 0; i < n; i++)
		fprintf(file, "Объект: %d; Класс: %d;\n", i, y[i]);
	fclose(file);
}

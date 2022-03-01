
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "help.h"
#include "kmeans.h"

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "RUS");
	if (argc < 6) {
		printf("Недостаточное число параметров!\n");
		exit(1);
	}
	int n = atoi(argv[1]), m = atoi(argv[2]), k = atoi(argv[3]);
	if ((n < 1) || (m < 1) || (k > n)) {
		printf("Некорректные значения параметров M, N или K!\n");
		exit(1);
	}
	double *x = (double*)malloc(n * m * sizeof(double));
	fscanf_data(x, n * m, argv[4]);
	int *res = (int*)malloc(n * sizeof(int));
	kmeans(x, res, n, m, k);
	fprintf_res(res, n, argv[5]);
	printf("Работа программы завершена!\n");
	free(x);
	free(res);
	return 0;
}

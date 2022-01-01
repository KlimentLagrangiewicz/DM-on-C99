
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "help.h"
#include "dbscan.h"

int main(void) {
	setlocale(LC_ALL, "RUS");
	int n, m;
	printf("Укажите число объектов для кластеризации=?\n");
	if (scanf("%d", &n) == 0) {}
	if (n < 1) {
		printf("Вы ввели некорректное значение!");
		exit(1);
	}
	printf("Укажите число их атрибутов=?\n");
	if (scanf("%d", &m) == 0) {}
	if (m < 1) {
		printf("Вы ввели некорректное значение!");
		exit(1);
	}
	double *x = (double*)malloc(n * m * sizeof(double));
	int *res = (int*) malloc(n * sizeof(int));
	char fd[70] = "//home//user//Рабочий стол//data//iris//test";
	char fr[70] = "//home//user//Рабочий стол//data//iris//result";
	fscanf_data(x, n * m, fd);
	double eps;
	printf("Укажите значение для eps=?\n");
	if (scanf("%lf", &eps) == 0) {}
	if (eps <= 0.0) {
		printf("Вы ввели некорректное значение!");
		exit(1);
	}
	int min_pts;
	printf("Укажите число соседей для образования ядра=?\n");
	if (scanf("%d", &min_pts) == 0) {}
	if (min_pts < 1) {
		printf("Вы ввели некорректное значение!");
		exit(1);
	}
	dbscan(x, res, n, m, min_pts, eps);
	fprintf_res(res, n, eps, min_pts, fr);
	printf("Работа программы завершена\n");
	free(x);
	free(res);
	return 0;
}

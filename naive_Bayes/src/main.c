
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "help.h"
#include "naive_bayes.h"

int main(void) {
	setlocale(LC_ALL, "RUS");
	int n, m, n2;
	printf("Укажите число объектов в обучающей выборке=?\n");
	if (scanf("%d", &n) == 0) {}
	if (n < 1) {
		printf("Вы указали некорректное значение!\n");
		exit(1);
	}
	printf("Укажите число их атрибутов=?\n");
	if (scanf("%d", &m) == 0) {}
	if (m < 1) {
		printf("Вы указали некорректное значение!\n");
		exit(1);
	}
	double *x_tr = (double*)malloc(n * m * sizeof(double));
	int *y = (int*)malloc(n * sizeof(int));
	char tfn[70] = "//home//user//Рабочий стол//data//iris//iris150";
	fscanf_tr(x_tr, y, n, m, tfn);
	printf("Укажите число объектов в тестовой выборке=?\n");
	if (scanf("%d", &n2) == 0) {}
	if (n2 < 1) {
		printf("Вы указали некорректное значение!\n");
		exit(1);
	}
	double *x_ts = (double*)malloc(n2 * m * sizeof(double));
	char tsfn[70] = "//home//user//Рабочий стол//data//iris//test";
	fscanf_ts(x_ts, n2 * m, tsfn);
	int *res = (int*)malloc(n2 * sizeof(int));
	int noc = get_num_of_cl(y, n);
	bayes(x_ts, x_tr, y, noc, n, m, n2, res);
	char rfn[70] = "//home//user//Рабочий стол//data//iris//result";
	fprintf_res(res, n2, rfn);
	printf("Работа программы завршена!\n");
	free(y);
	free(x_tr);
	free(res);
	free(x_ts);
	return 0;
}

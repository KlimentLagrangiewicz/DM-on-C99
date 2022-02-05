
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "help.h"
#include "cmeans.h"

int main(void) {
	setlocale(LC_ALL, "RUS");
	int n, m, k;
	printf("Укажите число объектов=?\n");
	if (scanf("%d", &n) == 0) {}
	printf("Укажите число их атрибутов=?\n");
	if (scanf("%d", &m) == 0) {}
	printf("Укажите число кластеров=?\n");
	if (scanf("%d", &k) == 0) {}
	double *x = (double*)malloc(n * m * sizeof(double));
	char dfn[70] = "//home//user//Рабочий стол//data//iris//test";
	fscanf_data(x , n * m, dfn);
	double *r = (double*)malloc(n * k * sizeof(double));
	char rfn[70] = "//home//user//Рабочий стол//data//iris//result";
	cmeans(x, r, n, m, k);
	fprintf_data(r, n , k, rfn);
	printf("Работа программы завершена!\n");
	free(x);
	free(r);
	return 0;
}

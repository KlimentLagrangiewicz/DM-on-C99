
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "help.h"
#include "kmeans.h"

int main(void) {
	setlocale(LC_ALL, "RUS");
	int n, m, k;
	printf("Укажите число объектов для кластеризации=?\n");
	if (scanf("%d", &n) == 0) {}
	if (n < 1) {
		printf("Вы указали некорректное значение!\n");
		exit(1);
	}
	printf("Число их атрибутов=?\n");
	if (scanf("%d", &m) == 0) {}
	if (m < 1) {
		printf("Вы указали некорректное значение!\n");
		exit(1);
	}
	printf("Число кластеров=?\n");
	if (scanf("%d", &k) == 0) {}
	if (k > n) {
		printf("Вы указали некорректное значение для числа кластеров\n");
		exit(1);
	}
	double *x = (double*)malloc(n * m * sizeof(double));
	char data[70] = "//home//user//Рабочий стол//data//iris//test";
	char results[70] = "//home//user//Рабочий стол//data//iris//result";
	fscanf_data(x, n * m, data);
	int *res = (int*)malloc(n * sizeof(int));
	kmeans(x, res, n, m, k);
	fprintf_res(res, n, results);
	printf("Работа программы завершена!\n");
	free(x);
	free(res);
	return 0;
}

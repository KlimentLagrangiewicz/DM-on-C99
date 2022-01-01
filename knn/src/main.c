
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "help.h"
#include "knn.h"

int main(void) {
	setlocale(LC_ALL, "RUS");
	int N, M, N2, k;
	printf("Укажите мощность обучающей выборки=?\n");
	if (scanf("%d", &N) == 0) {}
	printf("Укажите число атрибутов=?\n");
	if (scanf("%d", &M) == 0) {}
	double *xtrain = (double*)malloc(N * M * sizeof(double));
	int *y = (int *)malloc(N * sizeof(int));
	printf("Укажите число соседей=?\n");
	if (scanf("%d", &k) == 0) {}
	char train[70] = "//home//user//Рабочий стол//data//wine//wine178";
	char test[70] ="//home//user//Рабочий стол//data//wine//test178";
	fscanf_train(xtrain, y, N, M, train);
	printf("Укажите число объектов в тестовой выборки=?\n");
	if (scanf("%d", &N2) == 0) {}
	double *xtest = (double*)malloc(N2 * M * sizeof(double));
	fscanf_test(xtest, N2 * M, test);
	int *res = (int*)malloc(N2 * sizeof(int));
	z_normalization(xtrain, N, M);
	z_normalization(xtest, N2, M);
	kNN(xtrain, y, xtest, res, N, M, N2, k);
	char result_[70] = "//home//user//Рабочий стол//data//wine//result";
	fprintf_res(res, N2, result_);
	printf("Работа программы завершена!\n");
	free(res);
	free(xtest);
	free(xtrain);
	free(y);
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "help.h"
#include "cart.h"

int main(void) {
	int N, N2, M;
	printf("Число объектов в обучающей выборке=?\n");
	scanf("%d", &N);
	if (N < 1) {
		printf("Некорректное число!\n");
		exit(1);
	}
	printf("Укажите число их атрибутов=?\n");
	scanf("%d", &M);
	if (M < 1) {
		printf("Некорректное число атрибутов!\n");
		exit(1);
	}
	printf("Число тестовых объектов=?\n");
	scanf("%d", &N2);
	if (N2 < 1) {
		printf("Некорректное число!\n");
		exit(1);
	}
	char train[70] = "//home//user//Рабочий стол//data//iris//iris9";
	char test[70] = "//home//user//Рабочий стол//data//iris//test";
	char result[70] = "//home//user//Рабочий стол//data//iris//result";
	double *x_train = (double*)malloc(N * M * sizeof(double));
	int *y = (int*)malloc(N * sizeof(int));
	double *x_test = (double*)malloc(N2 * M * sizeof(double));
	int *res = (int*)malloc(N2*sizeof(int));
	scanf_train(train, x_train, y, N, M);
	scanf_test(test, x_test, N2, M);
	btree *tree = (btree*)malloc(sizeof(btree));
	int noc = get_num_of_cl(y, N);
	int *start_num = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		start_num[i] = i;
    create_tree(tree, x_train, y, M, start_num, N, noc);
    answers(tree, x_test, N2, M, res);
	printf_res(result, res, N2);
	printf("Работа программы завершена!\n");
	printf("Печать дерева=?\n0 - нет;\n1 - да.\n");
	int flag = 0;
	scanf("%d", &flag);
	if (flag == 1) {
		flag = 0;
		bool *vect = (bool*)malloc(0 * sizeof(bool));
		char tree_file[70] = "//home//user//Рабочий стол//treee";
		fprintf_btree(tree_file, tree, vect, flag);
		//printf_btree(tree, vect, flag);
		free(vect);
	}
	printf("Работа программы завершена!\n");
	free(start_num);
	free(res);
	free(x_test);
	free(y);
	free(x_train);
	free_btree(tree);
	return 0;
}

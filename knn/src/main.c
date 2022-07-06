
#include <stdio.h>
#include <stdlib.h>

#include "help.h"
#include "knn.h"

int main(int argc, char* argv[]) {
	if (argc < 8) {
		printf("Not enough parameters...\n");
		exit(1);
	}
	int n = atoi(argv[1]), m = atoi(argv[2]), n2 = atoi(argv[3]), k = atoi(argv[4]);
	double *xtrain = (double*)malloc(n * m * sizeof(double));
	int *y = (int *)malloc(n * sizeof(int));
	fscanf_train(xtrain, y, n, m, argv[5]);
	double *xtest = (double*)malloc(n2 * m * sizeof(double));
	fscanf_test(xtest, n2 * n, argv[6]);
	int *res = (int*)malloc(n2 * sizeof(int));
	kNN(xtrain, y, xtest, res, n, m, n2, k);
	fprintf_res(res, n2, argv[7]);
	printf("Program is ending...\n");
	free(res);
	free(xtest);
	free(xtrain);
	free(y);
	return 0;
}

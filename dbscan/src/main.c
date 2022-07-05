
#include <stdio.h>
#include <stdlib.h>

#include "help.h"
#include "dbscan.h"

int main(int argc, char* argv[]) {
	if (argc < 7) {
		printf("Not enough parameters...\n");
		exit(1);
	}
	int n = atoi(argv[1]), m = atoi(argv[2]), min_pts = atoi(argv[3]);
	double eps = strtod(argv[4], NULL);
	double *x = (double*)malloc(n * m * sizeof(double));
	int *res = (int*) malloc(n * sizeof(int));
	fscanf_data(x, n * m, argv[5]);
	dbscan(x, res, n, m, min_pts, eps);
	fprintf_res(res, n, eps, min_pts, argv[6]);
	printf("Program is ending...\n");
	free(x);
	free(res);
	return 0;
}

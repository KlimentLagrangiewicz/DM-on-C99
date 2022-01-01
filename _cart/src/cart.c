#include "cart.h"

void add_binvect(bool **vect, int *size, const bool value) {
	*vect = (bool*)realloc(*vect, (*size + 1) * sizeof(bool));
	*(*vect + *size) = value;
	*size += 1;
}

void printf_binvect(const bool *vect,const int size) {
	for (int i = size - 1; i > -1; i--)
		printf("%d", vect[i]);
	printf("\n");
}

void copy_binvect(bool **arc,const bool *src,const int size) {
	*arc = (bool*)realloc(*arc, size * sizeof(bool));
	memcpy(*arc, src, size * sizeof(bool));
}

void copy_intvect(int **arc,const int *src,const int size) {
	*arc = (int*)realloc(*arc, size * sizeof(int));
	memcpy(*arc, src, size * sizeof(int));
}

void add_intvect(int **vect, int *size, const int value) {
	*vect = (int*)realloc(*vect, (*size + 1) * sizeof(int));
	*(*vect + *size) = value;
	*size += 1;
}

void printf_intvect(const int *vect,const int size) {
	for (int i = 0; i < size; i++)
		printf(" %d ", vect[i]);
	printf("\n");
}

void free_btree(btree *tree) {
	if (tree != NULL) {
		free_btree(tree->left);
		free_btree(tree->right);
		free(tree);
	}
}

void printf_btree(const btree *tree, bool *vect, const int size) {
	if (tree != NULL) {
		for (int i = size - 1; i >= 0; i--)
			printf("%d", vect[i]);
		printf(" ");
		if  ((tree->right == NULL) ||(tree->left == NULL)){
					printf("Это лист. ");
					printf("Класс: %d;\n",  tree->num_q);
		} else {
			if (size == 0)
				printf("Это корень. ");
			else printf("Это узел. ");
			printf("Разделяющее значение: %.2lf", tree->data);
			printf("; Номер атрибута: %d;\n", tree->num_q);
		}
		if (tree->right != NULL) {
			int r_size = size;
			bool *vect_r = (bool*)malloc(size*sizeof(bool));
			copy_binvect(&vect_r, vect, size);
			add_binvect(&vect_r, &r_size, false);
			printf_btree(tree->right, vect_r, r_size);
			free(vect_r);
		}
		if (tree->left != NULL) {
			int l_size = size;
			bool *vect_l = (bool*)malloc(size*sizeof(bool));
			copy_binvect(&vect_l, vect, size);
			add_binvect(&vect_l, &l_size, true);
			printf_btree(tree->left, vect_l, l_size);
			free(vect_l);
		}
	}
}

void fprintf_btree(const char filename[70], const btree *tree, bool *vect, const int size) {
	FILE *file;
	if ((file = fopen(filename,"a")) != NULL) {
		if (tree != NULL) {
			for (int i = size - 1; i >= 0; i--)
				fprintf(file, "%d", vect[i]);
			fprintf(file, " ");
			if  ((tree->right == NULL) ||(tree->left == NULL)){
						fprintf(file, "Это лист. ");
						fprintf(file, "Класс: %d;\n",  tree->num_q);
			} else {
				if (size == 0)
					fprintf(file, "Это корень. ");
				else fprintf(file, "Это узел. ");
				fprintf(file, "Разделяющее значение: %.2lf", tree->data);
				fprintf(file, "; Номер атрибута: %d;\n", tree->num_q);
			}
			fclose(file);
			if (tree->right != NULL) {
				int r_size = size;
				bool *vect_r = (bool*)malloc(size*sizeof(bool));
				copy_binvect(&vect_r, vect, size);
				add_binvect(&vect_r, &r_size, false);
				fprintf_btree(filename, tree->right, vect_r, r_size);
				free(vect_r);
			}
			if (tree->left != NULL) {
				int l_size = size;
				bool *vect_l = (bool*)malloc(size*sizeof(bool));
				copy_binvect(&vect_l, vect, size);
				add_binvect(&vect_l, &l_size, true);
				fprintf_btree(filename, tree->left, vect_l, l_size);
				free(vect_l);
			}
		}
	}
}

double calc_Gini(const double *x,const int m,const int *y,const int noc,const int *numbers,const int sch,const double data,const int k) {
	double gini = 0.0;
	int L = 0, R = 0;
	int *left = (int*)calloc(noc, sizeof(int));
	int *right = (int*)calloc(noc, sizeof(int));
    for (int i = 0; i < sch; i++) {
    	if (x[numbers[i] * m + k] > data) {
    		R++;
    		for (int j = 0; j < noc; j++)
    			if (y[numbers[i]] == j)
    				right[j]++;
    	} else {
    		L++;
    		for (int j = 0; j < noc; j++)
    			if (y[numbers[i]] == j)
    				left[j]++;
    	}
    }
    for (int i = 0; i < noc; i++)
    	gini += ((L != 0)?((double)left[i] * left[i]/L):0.0) + ((R != 0)?((double)right[i] * right[i]/R):0.0);
    free(left);
    free(right);
	return (double)sch - gini;
}

void get_data_atr(const double *x,const int *y,const int M,const int noc,const int *numbers,const int sch, double *data, int *k) {
	double opt_data = x[numbers[0]];
	int opt_k = 0;
	double min_gini = calc_Gini(x, M, y, noc, numbers, sch, opt_data, opt_k);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < sch; j++) {
			double cur_gini = calc_Gini(x, M, y, noc, numbers, sch, x[numbers[j] * M + i], i);
			if (cur_gini < min_gini) {
				min_gini = cur_gini;
				opt_k = i;
				opt_data = x[numbers[j] * M + i];
			}
		}
	}
	*data = opt_data;
	*k = opt_k;
}

bool list(const int *y,const int *numbers,const int sch) {
	bool flag = true;
	int value = y[numbers[0]];
	for (int i = 0; i < sch && flag; i++) {
		if (y[numbers[i]] != value)
			flag = false;
	}
	return flag;
}

void create_tree(btree *tree, const double *x,const int *y,const int M,const int *numbers,const int sch,const int noc) {
	if (!list(y, numbers, sch)) {
		double data;
		int k;
		get_data_atr(x, y, M, noc, numbers, sch, &data, &k);
		tree->data = data;
		tree->num_q = k;
		int nol = 0, nor = 0;
		int *lefts = (int*)malloc(0 * sizeof(int));
		int *rights = (int*)malloc(0 * sizeof(int));
		for (int i = 0; i < sch; i++) {
			if (x[numbers[i]* M + k] > data) {
				add_intvect(&rights, &nor, numbers[i]);
			} else {
				add_intvect(&lefts, &nol, numbers[i]);
			}
		}
		tree->right = (btree*)malloc(sizeof(btree));
		tree->left = (btree*)malloc(sizeof(btree));
		create_tree(tree->right, x, y, M, rights, nor, noc);
		free(rights);
		create_tree(tree->left, x, y, M, lefts, nol, noc);
		free(lefts);
	} else {
		tree->left = NULL;
		tree->right = NULL;
		tree->num_q = y[numbers[0]];
	}
}

int answer(const btree *tree, const double *X, const int M, const int l) {
	int an;
	if ((tree->left == NULL) || (tree->right == NULL))
		an = tree->num_q;
	else an = ((X[M * l + tree->num_q] > (tree->data))?
	answer(tree->right, X, M, l):answer(tree->left, X, M, l));
	return an;
}

void answers(const btree *tree, const double *X, const int N, const int M, int *answers) {
	for (int i = 0; i < N; i++) {
		answers[i] = answer(tree, X, M, i);
	}
}

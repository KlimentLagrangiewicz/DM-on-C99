#ifndef CART_H_
#define CART_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct btree btree;

struct btree {
	double data;
	int num_q;
	btree* left;
	btree* right;
};

void add_binvect(bool **vect, int *size, const bool value);
void printf_binvect(const bool *vect,const int size);
void copy_binvect(bool **arc,const bool *src,const int size);
void add_intvect(int **vect, int *size, const int value);
void copy_intvect(int **arc,const int *src,const int size);
void printf_intvect(const int *vect,const int size);
void free_btree(btree *tree);
void printf_btree(const btree *tree, bool *vect, const int size);
void fprintf_btree(const char filename[70], const btree *tree, bool *vect, const int size);
double calc_Gini(const double *x,const int m,const int *y,const int noc,const int *numbers,const int sch,const double data,const int k);
void get_data_atr(const double *x,const int *y,const int M,const int noc,const int *numbers,const int sch, double *data, int *k);
bool list(const int *y,const int *numbers,const int sch);
void create_tree(btree *tree, const double *x,const int *y,const int M,const int *numbers,const int sch,const int noc);
int answer(const btree *tree, const double *X, const int M, const int l);
void answers(const btree *tree, const double *X, const int N, const int M, int *answers);

#endif /* CART_H_ */

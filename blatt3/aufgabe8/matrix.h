#ifndef _MATRIX_H__
#define _MATRIX_H__

#include <stdio.h>

struct matrix{
	size_t rows;
	size_t columns;
	long **data;
};

typedef struct matrix Matrix;



Matrix* matrix_allocate(size_t rows, size_t columns);

Matrix* matrix_generate(size_t rows, size_t columns);

void matrix_fill(Matrix* A,long a);

int matrix_add(Matrix *A,Matrix *B,Matrix *Result);

int matrix_multiply(Matrix *A,Matrix *B,Matrix *Result);

void matrix_print(Matrix *A);

Matrix* matrix_read(FILE*);

void matrix_free(Matrix *A);




#endif

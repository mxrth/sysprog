#ifndef _MATRIX_H__
#define _MATRIX_H__

#include <stdio.h>

struct matrix{
	size_t rows;
	size_t columns;
	long **data;
};

typedef struct matrix Matrix;


/*Allocates the memory for a struct matrix and then for a long-matrix with the dimensions
 *specified in 'rows' and 'columns'
 *
 *CAT
 */
Matrix* matrix_allocate(size_t rows, size_t columns);

/*Calls matrix_allocate, then fills the matrix with random numbers
 *
 *MAX
 */
Matrix* matrix_generate_random(size_t rows, size_t columns);

/*Fills all the entries in the matrix with the value 'a'
 *
 *BEN
 */
void matrix_fill(Matrix* A,long a);

/*Checks the dimensions of A and B to determine if they can be added
 *Then it computes the sum and writes it in the matrix 'Result'
 *
 *Return:	0 when successful
 *		1 when there is an error (e.g. wrong dimensions)
 *
 *CAT 
 */
int matrix_add(Matrix *A,Matrix *B,Matrix *Result);


/*Checks the dimensions of A and B to determine if they can be multiplied
 *It also checks if 'Result' has the right dimensions to hold the result
 *Then it computes the product and writes it in the matrix 'Result'
 *
 *Return:	0 when successful
 *		1 when there is an error (e.g. wrong dimensions)
 *
 *CAT 
 */
int matrix_multiply(Matrix *A,Matrix *B,Matrix *Result);

/*
 *BEN
 */
Matrix* matrix_read(FILE*);

/*Prints the matrix
 *
 *BEN
 */
void matrix_print(Matrix *A);

/*
 *CAT
 */
void matrix_free(Matrix *A);




#endif

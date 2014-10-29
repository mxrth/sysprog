#include "matrix.h"
#include <stdlib.h>

Matrix* matrix_allocate(size_t rows, size_t columns) {
    Matrix *mat;
    size_t i;

    if(!( mat = malloc(sizeof(*mat) )) ) return NULL;
    mat->rows = rows;
    mat->columns = columns;
    mat->data = malloc( sizeof(*(mat->data)) * rows);
    if(!mat->data) return NULL;

    for(i = 0; i < rows; i++) {
	if(! (mat->data[i] = malloc(sizeof(*(mat->data[i]))*columns)) )
	    return NULL;
    }
    return mat;
}


void matrix_free(Matrix *A) {
	int i = 0;
	for(;i<A->rows;i++) {
	free(A->data[i]);
	}
	free(A->data);
	free(*mat);
}
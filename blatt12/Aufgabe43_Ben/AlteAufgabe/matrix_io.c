#include <stdio.h>

#include "matrix.h"
#include "util.h"


Matrix* matrix_read(FILE* text){
	size_t i,j;	
	size_t rows,columns;
	Matrix* A;	
	
	fscanf(text,"%zu %zu\n",&rows,&columns);
	
	A = matrix_allocate(rows,columns);		
	if(A==NULL){
		return NULL;
	}	

	for(i=0;i<A->rows;i++){
		for(j=0;j<A->columns;j++){
			fscanf(text,"%ld",&(A->data[i][j]));
		}
	}
	
	return A;
}

void matrix_print(Matrix *A){
	size_t i,j;
	printf("%zu %zu\n", A->rows, A->columns);
	for(i=0;i<A->rows;i++){
		for(j=0;j<A->columns;j++){
			printf("%ld ",A->data[i][j]);
		}
		printf("\n");		
	}		
	return;
}

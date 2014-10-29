#include "matrix.h"

void matrix_fill(Matrix* A,long a){
	size_t i,j;
	for(i=0;i<A->rows;i++){
		for(j=0;j<A->columns;j++){
			A->data[i][j] = a;
		}
	}
	return;
}


int matrix_add(Matrix *A,Matrix *B,Matrix *Result){
	/*check dimensions */
	if(A->rows != B->rows || A->rows != Result->rows ||A->columns != B->columns || A->columns != Result->columns) {
	return 1;
	}
	/*calculate */
	size_t i,j;
	for(i=0;i<A->rows;i++){
		for(j=0;j<A->columns;j++){
			Result->data[i][j] = A->data[i][j] + B->data[i][j];
		}
	}
	return 0;
}

int matrix_multiply(Matrix *A,Matrix *B,Matrix *Result){

	/*check dimensions */
	if(A->columns != B->rows || A->rows != Result->rows ||B->columns != Result->columns) {
	return 1;
	}
	/* calculate */
	size_t i,j,k,l;
	for(i=0;i<A->rows;i++){
		for(j=0;j<B->columns;j++){
			for(k=0;k<A->columns;k++){
				for(l=0;l<B->rows;l++){
					Result->data[i],[j] += A->data[i][k] * B->data[l][j];	
				}
			}
		}
	}
	return 0;		

}
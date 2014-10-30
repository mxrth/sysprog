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
	size_t i,j,k;
	for(i=0;i<A->rows;i++){
		for(k=0;k<B->columns;k++){
			for(j=0;j<A->columns;j++){				
					Result->data[i],[k] += A->data[i][j] * B->data[j][k];	
			}
		}
	}
	return 0;		

}
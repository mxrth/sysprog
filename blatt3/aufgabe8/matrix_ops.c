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

int can_add(Matrix *A, Matrix *B) {
    return A->rows == B->rows && A->columns == B->columns;
}

int can_multiply(Matrix *A, Matrix *B) {
    return A->columns == B->rows;
}


int matrix_add(Matrix *A,Matrix *B,Matrix *Result){
	/*check dimensions */
	if(!can_add(A,B) || A->rows != Result->rows || A->columns != Result->columns) {
	    return 0;
	}
	/*calculate */
	size_t i,j;
	for(i=0;i<A->rows;i++){
		for(j=0;j<A->columns;j++){
			Result->data[i][j] = A->data[i][j] + B->data[i][j];
		}
	}
	return 1;
}

int matrix_multiply(Matrix *A,Matrix *B,Matrix *Result){

	/*check dimensions */
	if(!can_multiply(A,B) || A->rows != Result->rows ||B->columns != Result->columns) {
	    return 0;
	}
	/* calculate */
	size_t i,j,k;
	for(i=0;i<A->rows;i++){
		for(k=0;k<B->columns;k++){
			for(j=0;j<A->columns;j++){				
					Result->data[i][k] += A->data[i][j] * B->data[j][k];	
			}
		}
	}
	return 1;		

}


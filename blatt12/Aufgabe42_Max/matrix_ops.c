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

typedef struct m_args {
    Matrix *A;
    Matrix *B;
    Matrix *Result;
    int start_row;
    int end_row;
} m_args;

int matrix_multiply(Matrix *A,Matrix *B,Matrix *Result){
	
	/*check dimensions */
	if(!can_multiply(A,B) || A->rows != Result->rows ||B->columns != Result->columns) {
	    return 0;
	}
	/* calculate */
	
	int n = 2;
	pthread_t workers[n];
	m_args worker_args[n];
	int block_size = Result->rows / n;
	int first_blo = Result->rows - (n-1)*block_size;
	int cur_start = 0;
	for(int i = 0; i < n; i++, cur_start += block_size) {
	    worker_args[i].A = A;
	    worker_args[i].B = B;
	    worker_args[i].Result = Result;
	    worker_args[i].start_row = i == 0 ? last_block
	    pthread_create(&workers[i], NULL, worker, work)
	}
	
	return 1;		

}

int worker() {
    for(i=0;i<A->rows;i++){
	for(k=0;k<B->columns;k++){
	    for(j=0;j<A->columns;j++){				
		Result->data[i][k] += A->data[i][j] * B->data[j][k];	
	    }
	}
    }
}


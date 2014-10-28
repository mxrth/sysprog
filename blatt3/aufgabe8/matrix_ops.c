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

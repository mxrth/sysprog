#include <stdio.h>

#include "matrix.h"



Matrix* matrix_read(FILE*){
	

}

void matrix_print(Matrix *A){
	size_t i,j;
	for(i=0;i<A->rows;i++){
		for(j=0;j<A->columns;j++){
			printf("%l ",A->data[i][j]);
		}
		printf("\n");		
	}		
	return;
}

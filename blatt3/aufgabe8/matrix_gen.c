#include "matrix.h"
#include <stdlib.h>

Matrix* matrix_generate_random(size_t rows, size_t columns) {
    Matrix* mat;
    size_t i, j;
    long** m;
    if(! (mat = matrix_allocate(rows, columns)) ) return NULL;
    m = mat->data;
    for(i = 0; i < rows; i++) {
	for(j = 0; j < columns; j++) {
	    m[i][j] = generate_random();
	}
    }
}


long generate_random() {
    long negative = random() % 2;
    if(negative) return (-1)*random();
    else return random();
}

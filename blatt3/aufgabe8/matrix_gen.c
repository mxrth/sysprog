#include "matrix.h"
#include <stdlib.h>
#include <time.h> /*for seeding*/
long generate_random(void);

void seed_random(void);

Matrix* matrix_generate_random(size_t rows, size_t columns, int max) {
    Matrix* mat;
    size_t i, j;
    long** m;
    if(! (mat = matrix_allocate(rows, columns)) ) return NULL;
    m = mat->data;
    
    seed_random();

    for(i = 0; i < rows; i++) {
	for(j = 0; j < columns; j++) {
	    m[i][j] = generate_random();
	}
    }
    return mat;
}

void seed_random(void) {
    srand((unsigned) time(NULL));
}

long generate_random(void) {
    long negative = rand() % 2;
    if(negative) return (-1)*rand();
    else return rand();
}

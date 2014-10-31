#include "matrix.h"
#include <stdlib.h>
#include <time.h> /*for seeding*/
#include <limits.h>

int generate_random(int);

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
	    m[i][j] = generate_random(max);
	}
    }
    return mat;
}

void seed_random(void) {
    srand((unsigned) time(NULL));
}

/* int x = bedingung ? wert_wahr : wert_falsch; */

int generate_random(int max) {
    int negative = rand() % 2;
    int r = rand() % ((max < 0) ? INT_MAX  : max) ;
    if(negative) return -r;
    else return r;
}

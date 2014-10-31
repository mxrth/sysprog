#include "matrix.h"
#include "util.h"

void print_id(size_t rows); 

int main(int argc, char *argv[]) {
    size_t rows=0, columns=0;
    Matrix *m;
    int max = -1;
    if(argc < 3) {
	ERROR("Please specify number of rows and columns\n");
    }
    sscanf(argv[1], "%zu", &rows);
    sscanf(argv[2], "%zu", &columns);
    if(argc == 4) {
	if(argv[3][0] == 'i') { print_id(rows); return 0;}
	sscanf(argv[3], "%d", &max);
    }
    if(rows <= 0 || columns <= 0)
	ERROR("Invalid number of rows or columns\n");
    
    m = matrix_generate_random(rows, columns, max);
    if(!m) ERROR("Could not generate matrix\n");
    matrix_print(m);
    matrix_free(m);
    return 0;
}

void print_id(size_t rows) {
    size_t i, j;
    printf("%zu %zu\n", rows, rows);
    for(i = 0; i < rows; i++) {
	for(j = 0; j < rows; j++) {
	    if(i == j) printf("1");
	    else printf("0");
	    if(j < rows - 1) printf(" ");
	}
	printf("\n");
    }
}

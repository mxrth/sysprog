#include "matrix.h"
#include "util.h"

int main(int argc, char *argv[]) {
    size_t rows=0, columns=0;
    Matrix *m;
    if(argc != 3) {
	ERROR("Please specify number of rows and columns");
    }
    sscanf(argv[1], "%zu", &rows);
    sscanf(argv[2], "%zu", &columns);
    if(rows <= 0 || columns <= 0)
	ERROR("Invalid number of rows or columns");
    
    m = matrix_generate_random(rows, columns);
    if(!m) ERROR("Could not generate matrix");
    matrix_print(m);
    return 0;
}

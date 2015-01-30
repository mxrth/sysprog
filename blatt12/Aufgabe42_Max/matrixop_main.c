#include "matrix.h"
#include "util.h"
#include <stdio.h>

typedef enum Operation {
    ADD , 
    MULTIPLY,
    UNKNOWN
} Operation;

int parse_input(int argc, char* argv[], FILE** in_A, FILE** in_B, Operation* op);
Operation parse_op(char* op);
int can_do_operation(Operation op, Matrix* A, Matrix* B);
Matrix* do_operation(Operation op, Matrix *A, Matrix* B);

int main(int argc, char* argv[]) {
    FILE *infile_A, *infile_B;
    Operation op;
    Matrix *A, *B, *Result;
    if(!parse_input(argc, argv, &infile_A, &infile_B, &op)) {
	ERROR("Invalid prameters. \nUsage: matrixops <matrix_A_file> [a[dd]|m[ultiply]] <matrix_B_file>");
    }
    if( !(A = matrix_read(infile_A)) ) ERROR("Could not read first input file");
    if( !(B = matrix_read(infile_B)) ) ERROR("Could not read second input file");
    if(!can_do_operation(op, A, B)) ERROR("Invalid dimensions");
    if( !(Result = do_operation(op, A, B)) ) ERROR("Internal Error, OOM?");
    
    matrix_print(Result);
    matrix_free(A); matrix_free(B); matrix_free(Result);
    fclose(infile_A); fclose(infile_B);

}

int parse_input(int argc, char* argv[], FILE **in_A, FILE **in_B, Operation* op) {
    if(argc != 4) {printf("%d\n", argc); return 0;}
    if( !(*in_A = fopen(argv[1], "r")) ) return 0;
    if( !(*in_B = fopen(argv[3], "r")) ) return 0;
    if( (*op = parse_op(argv[2])) == UNKNOWN) return 0;
    return 1;
}

Operation parse_op(char* op) {
    if(op[0] == '\0') return UNKNOWN; /*String is empty (Should not happen)*/
    if(op[0] == 'm') return MULTIPLY;
    if(op[0] == 'a') return ADD;
    return UNKNOWN;
}

int can_do_operation(Operation op, Matrix* A, Matrix* B) {
    if(op == ADD) return can_add(A,B);
    if(op == MULTIPLY) return can_multiply(A,B);
    return 0;
}

Matrix *do_operation(Operation op, Matrix* A, Matrix *B) {
    Matrix *Result;
    if(op == ADD) {
	if( !(Result = matrix_allocate(A->rows, A->columns)) ) return NULL;
	if(!matrix_add(A, B, Result)) return NULL;
    }
    else if(op == MULTIPLY) {
	if( !(Result = matrix_allocate(A->rows, B->columns)) ) return NULL;
	if(!matrix_multiply(A, B, Result)) return NULL;
    }
    else return NULL;
    return Result;
}


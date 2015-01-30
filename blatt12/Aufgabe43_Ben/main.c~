#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "matrix.h"
#include "util.h"

int parse_input(int argc, char* argv[], FILE **in_A, FILE **in_B, int* thread_count);

int main(int argc, char* argv[]) {
    FILE *infile_A, *infile_B;
    int thread_count;
    Matrix *A, *B, *Result;
	struct matrix_multiply_args** args_array;    
	pthread_t *threads_array;
	
	if(!parse_input(argc, argv, &infile_A, &infile_B, &thread_count)) {
	ERROR("Invalid prameters. \nUsage: matrix_threads <matrix_A_file> <matrix_B_file> [Number of threads]");
    }
    if( !(A = matrix_read(infile_A)) ) ERROR("Could not read first input file");
    if( !(B = matrix_read(infile_B)) ) ERROR("Could not read second input file");
    if( !(can_multiply(A, B)) ) ERROR("Invalid dimensions");
    
	if( !(Result = matrix_allocate(A->rows, B->columns)) ) ERROR("Could not allocate memory for the result");
	
	
	if( !(args_array = malloc(thread_count*sizeof(struct matrix_multiply_args*))) ) ERROR("Error in malloc")
	if( !(threads_array = malloc(thread_count*sizeof(pthread_t))) ) ERROR("Could not allocate memory")
	

    matrix_print(Result);
	
	
    matrix_free(A); matrix_free(B); matrix_free(Result);
	free(args_array); free(threads_array);
    fclose(infile_A); fclose(infile_B);

}


int prepare_matrix_multiply_args(struct matrix_multiply_args** args_array, int thread_count, Matrix *A, Matrix* B, Matrix *Result){
	printf("Dristibuting %zu rows on %i threads", A->rows, thread_count);
	if(thread_count < A->rows){
		ERROR("ABORTING More threads than lines! This situation is not implemented yet");	
	}
	
	int lines_per_thread = (A->rows)/thread_count;
	int rest = (A->rows) % thread_count;
	
	for(size_t i = 0; i < thread_count ; i++){
		args_array[i] = malloc(sizeof(struct matrix_multiply_args));
		if(args_array[i] == NULL) ERROR("Error in malloc");
		args_array[i]->A = A;
		args_array[i]->B = B;
		args_array[i]->Result = Result;
		args_array[i]->starting_row = i*lines_per_thread;
		args_array[i]->lines_to_process = lines_per_thread;
	}

	return 0;
}
int parse_input(int argc, char* argv[], FILE **in_A, FILE **in_B, int* thread_count) {
    if(argc != 4) {printf("%d\n", argc); return 0;}
    if( !(*in_A = fopen(argv[1], "r")) ) return 0;
    if( !(*in_B = fopen(argv[2], "r")) ) return 0;
    *thread_count = atoi(argv[3]);
    return 1;
}


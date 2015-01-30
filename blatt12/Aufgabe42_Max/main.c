#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

#define ERROR(s) {printf("ERROR:\n %s \n\n",s);exit(1);}

/*The program expects one argument:
 *The user has to enter the name of a .txt file in which a matrix is stored.
 *The first line contains the number of rows and columns seperated by a space ' '
 *After this the lines of the matrix follow. Each value is seperated from the next by a space ' '
 *After each row of matrix data there has to be a new line
 *
 *Example:
 *===Begin of file===
 *5 5
 *7 8 6 4 5
 *5 8 4 2 5
 *7 -8 7 -45 5
 *-7 8 2 -23 5
 *7 -8 9 3 5
 *===End of file===
 */
int main(int argc, char* argv[]){
	FILE* text;
	Matrix *A;
	Matrix *B;

	B = matrix_allocate(7,9);
	matrix_fill(B,-78);

	if(argc < 2){
		ERROR("Not the right amount of arguments")
	}
	
	text = fopen(argv[1],"r");
	
	if(text == NULL){
		ERROR("Could not locate the file")	
	}

	A=matrix_read(text);
	if(A==NULL){
		ERROR("Fehler beim Einlesen der Matrix")
	}
	free(B)
	B = matrix_read(fopen(argv[2], "r");
	fclose(text);
	
	printf("Matrix A:\n");
	matrix_print(A);
	printf("Matrix B:\n");
	matrix_print(B);

	return 0;
}

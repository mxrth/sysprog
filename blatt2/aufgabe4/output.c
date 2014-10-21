/*Benoetigt fuer:
 *
 */
#include "output.h"

/*Benoetigt fuer:
 *struct t_brett
 *
 */
#include "brett.h"

/*Benoetigt fuer:
 *printf
 */
#include <stdio.h>

/*gibt aktuelles Schachbrett aus */
void print_brett(struct t_brett *b){
	int i;
	for(i=0;i<b->dimension;i++){
		print_seperating_line(b->dimension);
		printf("\n");
		print_array_line(b, i);
		printf("\n");
	}
	print_seperating_line(b->dimension);
	printf("\n\n");
	return;
}

/*Assumption: n is an integer >1
 *
 *Result: prints n instances of +---+ in the command line
 */
void print_seperating_line(int length){
	int i;
	for(i=0;i<length;i++){
		printf("+---");
	}
	printf("+");
	return;
}

/*Assumption: b is an initialized struct t_brett, n is an integer with 1<= n <=b->dimension
 *
 *Result: prints the nth line of the chess board, colums seperated by "+"
 */
void print_array_line(struct t_brett* b, int n){
	int i;
	for(i=0;i<b->dimension;i++){
		printf("+%3i",b->felder[n][i]);
	}
	printf("+");
}

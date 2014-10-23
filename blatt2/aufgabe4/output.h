#ifndef __OUTPUT_H_
#define __OUTPUT_H_

/*Benoetigt fuer:
 *struct t_brett
 *
 */
#include "brett.h"

/*gibt aktuelles Schachbrett aus */
void print_brett(struct t_brett *b);

/*Assumption: n is an integer > 1
 *
 *Result: prints n instances of +---+ in the command line
 */
void print_seperating_line(int length);

/*Assumption: b is an initialized struct t_brett, n is an integer with 1<= n <=b->dimension
 *
 *Result: prints the nth line of the chess board, colums seperated by "+"
 */
void print_array_line(struct t_brett* b, int n);



#endif


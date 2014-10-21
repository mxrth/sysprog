#include <stdlib.h>
#include <stdio.h>
#include "brett.h"

int main() {

	struct t_brett b;
	int n = 4;
	int x = 3;
	int y = 2;
	int ergebnis;

	/*Test für init_brett und allocate*/

	ergebnis = init_brett(&b,n,x,y);

	if(ergebnis == 1){
		printf("MEMORY ERROR\n");
	}
	else{
		printf("Speicher allokiert\n");
	}

	ergebnis = frei(&b, 1, 1);

	if(ergebnis == 0){
			printf("belegt\n");
		}
		else{
			printf("frei\n");
		}

	ergebnis = frei(&b, 3, 2);

	if(ergebnis == 0){
			printf("belegt\n");
		}
		else{
			printf("frei\n");
		}


	int f = (*(&b)).dimension;
	printf("f=%i\n",f);
	/*Test besuchte_felder*/

	int a = besuchte_felder(&b);
	printf("Besuchte Felder: %i \n",a);

	loesche_brett(&b);
	return 0;
}

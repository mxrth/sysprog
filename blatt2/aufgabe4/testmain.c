/*
 * testmain.c
 *
 *  Created on: 21.10.2014
 *      Author: claire
 */


#include <stdlib.h>
#include "brett.h"
#include <stdio.h>

int main() {

	struct t_brett b;
	int n = 4;
	int x =3;
	int y =2;
	int ergebnis;

	/*Test für init_brett und allocate*/

	ergebnis = init_brett(&b,n,x,y);

	if(ergebnis == 1){
		printf("Es hat leider nicht geklappt\n");
	}
	else{
		printf("läuft\n");
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

	return 0;
}

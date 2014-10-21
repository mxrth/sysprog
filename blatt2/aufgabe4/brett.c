/*Benoetigt fuer:
 *malloc
 */
#include <stdlib.h>
#include "brett.h"

/*Erzeugt das int-array
 *Gibt NULL zurueck, wenn in einem Schritt kein Speicher allokiert werden konnte
 */
int** allocate_feld(int n){
	int i = 0;
	int** feld = malloc(n*sizeof(int*));
	if(feld==NULL){
		return NULL;
	}
	for(i=0;i<n;i++){
		feld[i] = malloc(n*sizeof(int));
		if(feld[i]==NULL){
			return NULL;
		}
	}
	return feld;
}

int init_brett(struct t_brett *b, int n, int x, int y){
	(&b).felder = allocate_feld(n);
	if(&b != NULL) {
	(&b).felder[x][y] = 1;
	return 1;
	}
	return 0;
}
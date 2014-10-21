/*Benoetigt fuer:
 *malloc
 */
#include <stdlib.h>
#include "brett.h"
#include <stdio.h>

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

/*Führt Initialisierung des Schachbrettes durch.
Ruft allocate_feld auf und übergibt die Dimension des Feldes. Markiert Startposition im Feld. Gibt 0 zurück, wenn Initialisierung nicht durchgeführt werden konnte*/
int init_brett(struct t_brett *b, int n, int x, int y){
	(*b).felder = allocate_feld(n);
	(*b).dimension = n;
	if((*b).felder != NULL) {
	(*b).felder[x][y] = 1;
	return 1;
	}
	return 0;
}


/* Bewegt Springer um x Felder in die Horizontalen und um y Felder in der Vertikalen.
Berechnet die neue Position und markiert das entsprechende Feld als besucht*/
int neuer_sprung(struct t_brett *b, int x, int y);

/*Macht den Sprung (x,y) rückgängig und entfernt die Markierung */
int entferne_sprung(struct t_brett *b, int x, int y);

/*Liefert Wert ob das Feld noch besucht werden kann*/
int frei(struct t_brett *b, int x, int y) {
	if((*b).felder[x][y] >0) {
		return 0;
	}
		return 1;
}

/*Liefert Anzahl an Feldern, die schon vom Springer besucht worden sind*/
int besuchte_felder(struct t_brett *b);

/*Gibt reservierten Speicher wieder frei*/
void loesche_brett(struct t_brett *b);
/*Assumptions:
 *brett ist ein pointer auf eine struct t_brett, in dieser Struct ist bereits Speicher fuer das int-array allokiert
 *
 *
 */
int fill_brett(struct t_brett* brett, int a){
	int i,j;
	for(i=0;i<brett->dimension;i++){
		for(j=0;j<brett->dimension;j++){
			brett->felder[i][j] = a;
		}
	}
	return 0;
}


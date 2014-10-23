/*Benoetigt fuer:
 *malloc
 */
#include <stdlib.h>

/*Wofuer brauchen wir das?*/
#include <stdio.h>

/*Benoetigt fuer:
 *struct t_brett
 */
#include "brett.h"

/*Benoetigt fuer:
 *print_brett
 */
#include "output.h"

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
 *Ruft allocate_feld auf und übergibt die Dimension des Feldes. 
 *Ruft fill_brett auf und setzt alle Felder auf 0.
 *Markiert Startposition im Feld. 
 *Gibt 1 zurück, wenn Initialisierung nicht durchgeführt werden konnte*/
int init_brett(struct t_brett *b, int n, int x, int y) {
	(*b).dimension = n;
	(*b).felder = allocate_feld(n);
	if ((*b).felder == NULL) {
		return 1;
	}
	print_brett(b);
	fill_brett(b, 0);
	print_brett(b);
	(*b).felder[x][y] = 1;
	print_brett(b);
	return 0;
}



/* Bewegt Springer um x Felder in die Horizontalen und um y Felder in der Vertikalen.
Berechnet die neue Position und markiert das entsprechende Feld als besucht*/
int neuer_sprung(struct t_brett *b, int x, int y);

/*Macht den Sprung (x,y) rückgängig und entfernt die Markierung */
int entferne_sprung(struct t_brett *b, int x, int y);

/*Liefert Wert ob das Feld noch besucht werden kann. Liefert 0, wenn Feld besetzt ist oder nicht existiert.*/
int frei(struct t_brett *b, int x, int y) {
	int n = b->dimension;
	if(x>=n || y>=n || x<0 || y<0 || b->felder[x][y] > 0)  {
		return 0;
	}
	else return 1;
}

/*Liefert Anzahl an Feldern, die schon vom Springer besucht worden sind*/
int besuchte_felder(struct t_brett *b) {
	int zaehler = 0;
	int i;
	int j;
	int n = (*b).dimension;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if ((((*b).felder)[i][j]) > 0) {
				zaehler++;
			}
		}
	}
	return zaehler;
}

/*Gibt reservierten Speicher wieder frei*/
void loesche_brett(struct t_brett *b){
	int i = 0;
	for(i=0;i<(b->dimension);i++){
		free(b->felder[i]);
	}
	free(b->felder);
	return;
}

/*Assumptions:
 *brett ist ein pointer auf eine struct t_brett, in dieser Struct ist bereits Speicher fuer das int-array allokiert
 *
 *Result: Schreibt den Wert von a in alle Felder der Matrix
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


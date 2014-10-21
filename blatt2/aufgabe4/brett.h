#ifndef __BRETT_H_
#define __BRETT_H_

/*Definition des Schachfeldes*/
struct t_brett{
 int** felder;
 int dimension;
};

/*Führt Initialisierung des Schachbrettes durch ( Übergabe per Zeiger als 1.Parameter)
Ruft allocate_feld auf. Markiert Startposition im Feld. Gibt 0 zurück, wenn Initialisierung nicht durchgeführt werden konnte*/
int init_brett(struct t_brett *b, int n, int x, int y);

/*Allokiert Speicher für das Feld
Gibt NULL zurueck, wenn in einem Schritt kein Speicher allokiert werden konnte
*/
int** allocate_feld(int n);

/* Bewegt Springer um x Felder in die Horizontalen und um y Felder in der Vertikalen.
Berechnet die neue Position und markiert das entsprechende Feld als besucht*/
int neuer_sprung(struct t_brett *b, int x, int y);

/*Macht den Sprung (x,y) rückgängig und entfernt die Markierung */
int entferne_sprung(struct t_brett *b, int x, int y);

/*Liefert Wert ob das Feld noch besucht werden kann*/
int frei(struct t_brett *b, int x, int y);

/*Liefert Anzahl an Feldern, die schon vom Springer besucht worden sind*/
int besuchte_felder(struct t_brett *b);

/*Gibt reservierten Speicher wieder frei*/
void loesche_brett(struct t_brett *b);


#endif /* BRETT_H_ */
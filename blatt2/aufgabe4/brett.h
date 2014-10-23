#ifndef __BRETT_H_
#define __BRETT_H_

/*Definition des Schachfeldes*/
struct t_brett{
	int** felder;
	int dimension;
	int pos_x;
	int pos_y;
};

/* Easy accesors */
#define CUR_FELD(b) FELD_OFFSET(b, 0, 0)
#define FELD_OFFSET(b, x, y) ( (b)->felder[(b)->pos_x + (x)][(b)->pos_y + y] )



/*Führt Initialisierung des Schachbrettes durch.
 *Ruft allocate_feld auf und übergibt die Dimension des Feldes.
 *Ruft fill_brett auf und setzt alle Felder auf 0.
 *Markiert Startposition im Feld mit "1".
 *Gibt 1 zurück, wenn Initialisierung nicht durchgeführt werden konnte*/
int init_brett(struct t_brett *b, int n, int x, int y);

/*Assumptions: n is a positive integer
 *
 *Result:
 *Allokiert Speicher für das Feld
 *Gibt NULL zurueck, wenn in einem Schritt kein Speicher allokiert werden konnte
 */
int** allocate_feld(int n);

/*Fuellt das Brett komplett mit dem Wert spzifieziert in der Variable a*/
int fill_brett(struct t_brett* brett, int a);

/* Bewegt Springer um x Felder in die Horizontalen und um y Felder in der Vertikalen.
Berechnet die neue Position und markiert das entsprechende Feld als besucht*/
int neuer_sprung(struct t_brett *b, int x, int y);

/*Macht den Sprung (x,y) rückgängig und entfernt die Markierung */
int entferne_sprung(struct t_brett *b, int x, int y);

/*Liefert Wert ob das Feld noch besucht werden kann*/
/*FALSCH SPEZIFIZIERT IN AUFGABENSTELLUNG:
 * _soll_ überprüfen ob der SPRUNG (x, y) noch frei ist m) */
int frei(struct t_brett *b, int x, int y);

/*Liefert Anzahl an Feldern, die schon vom Springer besucht worden sind*/
int besuchte_felder(struct t_brett *b);

/*Gibt reservierten Speicher wieder frei*/
void loesche_brett(struct t_brett *b);


#endif /* BRETT_H_ */

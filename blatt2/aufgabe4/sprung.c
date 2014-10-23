#include "brett.h"

#define CUR_FELD(b) FELD_OFFSET(b, 0, 0)
#define FELD_OFFSET(b, x, y) ( (b)->felder[(b)->pos_x + (x)][(b)->pos_y + y] )

/* Bewegt Springer um x Felder in die Horizontalen und um y Felder in der Vertikalen.
Berechnet die neue Position und markiert das entsprechende Feld als besucht*/
int neuer_sprung(struct t_brett *b, int x, int y) {
    int naechste_nummer = besuchte_felder(b)+1;
    FELD_OFFSET(b, x, y) = naechste_nummer;
    return 1;
}

/*Macht den Sprung (x,y) rückgängig und entfernt die Markierung */
int entferne_sprung(struct t_brett *b, int x, int y) { 
    CUR_FELD(b) = 0;
    b->pos_x = x;
    b->pos_y = y;
    return 0;
}



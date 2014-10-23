#include "brett.h"

/* Bewegt Springer um x Felder in die Horizontalen und um y Felder in der Vertikalen.
Berechnet die neue Position und markiert das entsprechende Feld als besucht*/
int neuer_sprung(struct t_brett *b, int x, int y) {
    FELD_OFFSET(b, x, y) = CUR_FELD(b)+1;
    b->pos_x += x;
    b->pos_y += y;
    return 1;
}

/*Macht den Sprung (x,y) rückgängig und entfernt die Markierung */
int entferne_sprung(struct t_brett *b, int x, int y) { 
    CUR_FELD(b) = 0;
    b->pos_x -= x;
    b->pos_y -= y;
    return 0;
}



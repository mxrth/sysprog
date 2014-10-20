

/*Initialisierung des Feldes*/
int** felder

/* Bewegt Springer um x Felder in die Horizontalen und um y Felder in der Vertikalen.
Berechnet die neue Position und markiert das entsprechende Feld als besucht*/
int neuer_sprung(struct t_brett *b, int x, int y);

/*Macht den Sprung (X,y) rückgängig und entfernt die Markierung */
int entferne_sprung(struct t_brett *b, int x, int y);

/*Liefert Wert ob das Feld noch besucht werden kann*/
int frei(struct t_brett *b, int x, int y);

/*Liefert Anzahl an Feldern, die schon vom Springer besucht worden sind*/
int besuchte_felder(struct t_brett *b);

/*gibt aktuelles Schachbrett aus */
void print(struct t_brett *b);

/*Führt Initialisierung des Schachbrettes durch ( Übergabe per Zeiger als 1.Parameter) */
int init_brett(struct t_brett *b, int n, int x, int y);

/*Gibt reservierten Speicher wieder frei*/
void loesche_brett(struct t_brett *b);
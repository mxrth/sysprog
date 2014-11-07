
<string.h> ist nicht included, deshalb wird die Funktion strlen nicht gefunden
<ctype.h> ist nicht included, deshalb wird die Funktion toupper nicht gefunden

In Zeile 17: Zeichenkonstante mit mehreren Zeichen
Ursprünglich:  char *exit = 'exit';
Korrigiert:    char *exit = "exit";

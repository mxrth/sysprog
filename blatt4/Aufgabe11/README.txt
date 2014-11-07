
<string.h> ist nicht included, deshalb wird die Funktion strlen nicht gefunden
<ctype.h> ist nicht included, deshalb wird die Funktion toupper nicht gefunden

In Zeile 17: Zeichenkonstante mit mehreren Zeichen
Ursprünglich:  char *exit = 'exit';
Korrigiert:    char *exit = "exit";

Warning : Feldindex hat Type char
Typecast zu Integer bei 
(toupper((int)st1[i]) != toupper((int)st1[st1_len -i])) und
toupper((int)st1[st1_len -1 -i]);

palindrom_check1 vergleicht den i.Buchstaben mit dem, von hinten gezählt,
i.Buchstaben. Dafür muss aber
toupper((int)st1[st1_len -i -1]
statt
toupper((int)st1[st1_len -i]
betrachtet werden, da das Array von 0 bis st1_len-1 indiziert ist.
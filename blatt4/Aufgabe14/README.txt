
(a) p = feld;
Ist zulässig, denn der Name des Arrays ist äquivalent 
zu einem Pointer auf sein erstes Element.

(b) feld = p;
Ist nicht zulässig. Der Name des Arrays ist ein konstanter Pointer, 
das heißt man kann nicht verändern auf welchen Speicherbereich er zeigt.

(c) p = &feld[3];
Ist zulässig. Erst wird mit feld[3] das int ausgewertet, welches an 4.Stelle im Array steht. Dann durch das & ein Pointer auf dieses int. Dieser Intpointer wird dann p zugewiesen.

(d) feld[2] = p[5];
Ist zulässig. p[5] ist äquivalent zu *(p+5). Das heißt der 3.Position des 
Arrays wird der (wohlmöglich unbekannte) Inhalt von *(p+5) zugewiesen, wobei dieser als Integer interpretiert wird.
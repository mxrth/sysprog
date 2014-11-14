Zeile 7 ff.: Ändere in char**, da main später noch auf den pointer zugreifen soll.

Zeile 19: long int ist != size_t und insbesondere unsigned

Zeile 21: format identifier für size_t ist %zu (c99) nicht %lu

Zeile 23: Format für Pointer ist %p

Angestrebte Semantik ist nicht klar, 
das programm gibt nun maximalen wert in mb aus, für den malloc einen nicht-NULL wert zurück gibt, die aussagekraft über tatsächlich verfügbaren Speicher ist gleich null. 

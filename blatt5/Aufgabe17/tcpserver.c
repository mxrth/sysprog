#include <stdio.h>

#include "unp_readline.c"

// includes etc.

int main(int argc, char **argv)
{
	int anzverbindungen;
	int portnummer;
	// ...

	if (prepare_socket(portnummer)) {
		printf("Fehler beim Erzeugen / binden des Sockets\n");
		return 1;
	}
	anzverbindungen = manage_connections(anzverbindungen, &manager);
	printf("%d Verbindungen wurden behandelt.\n", anzverbindungen);
	close_socket();
	return 0;
}

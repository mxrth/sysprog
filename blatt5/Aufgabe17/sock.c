// includes etc.

int serversocket = 0;

int prepare_socket(int portnum)
{
	// ...
}

void close_socket(void)
{
	// ...
}

int manage_connections(int anzverbindungen, int (*managerfunction) (FILE * datastream, char *information))
{
	// ...
}


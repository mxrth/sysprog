#include <stdio.h>

void get_input_console (char *message)
{
	printf ("Please input a message that you want to send (max. length 255 characters)\n");
	scanf ("%255s", message);
	return;
}

/*
void print_struct_sockaddr_in(struct sockaddr_in *dest){
	

}
*/

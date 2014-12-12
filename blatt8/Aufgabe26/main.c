#include <stdio.h>
#include "rot13.h"


int main(){
	char mystring[10] = "Hallo";
	rot13_str(mystring);

	printf("%s\n",mystring);

	return 0;
}

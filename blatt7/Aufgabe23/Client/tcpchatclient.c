#include <stdio.h>

int get_nickname(char* nickname){
	int err;
    char user_input[30];
	
    printf("Please enter your nickname (max. 30 characters):\n");
	fgets(user_input,30,stdin);
    return sscanf(user_input, "%s", nickname);
}

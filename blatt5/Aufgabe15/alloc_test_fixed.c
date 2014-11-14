#include<stdio.h>
#include<stdlib.h>
#include <stdint.h>
#define MB 1024

/*Use a double pointer here, rationale given below in main()*/
size_t alloc_test(char **c){
    size_t mb=1;
       
    while ( ( *c = (char*) malloc(mb*MB) ) != NULL) {
	free (*c);
	mb++;
    }
    while ((*c=(char*) malloc((--mb)*MB)) == NULL);
	  
    return mb;
}

int main(void){
    char* c;
    /*use size_t to be on the safe side*/
    size_t size;
    /*When passing c with type `char* c like this`, it is passed by value, 
     * so later writes by alloc_test will have no effect*/
    /*Using a double pointer here instead would work*/
    size = alloc_test(&c);
    printf("Zur Verfügung stehender Speicher in Megabyte: %zu\n", size);
    if (size>0) {
	/*Do not use %s to print adresses, use %p instead!*/
        printf("Reservierter Speicher mit Addresse %p wird nun freigegeben...\n", c);
        free (c);
    }
    return 0;
}


#include <stdio.h>

int global_noint;
int global_intzero = 0;
int global_intone = 1;

const int global_const = 2;

int main(void) {
    printf("%d %d %d %d\n", global_noint, global_intzero, global_intone, global_const);
}

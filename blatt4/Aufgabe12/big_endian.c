#include <stdint.h>
#include <stdio.h>

int big_endian(void) {
    uint16_t test_bytes = 0xFFAA;
    uint8_t low_byte = *( (uint8_t *) &test_bytes);
    if(low_byte == 0xFF) return 1;
    else return 0;
}

int main(void) {
    if(big_endian()) printf("Big endian!\n");
    else printf("Little endian!\n");
}


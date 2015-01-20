CFLAGS = -m32

all: matrix_mul 

mmul.o: mmul.asm
	as --32 -g --gstabs -o mmul.o  mmul.asm

matrix.o: matrix.c

matrix_mul: mmul.o matrix.o
	gcc -m32 -o  matrix_mul mmul.o matrix.o


clean:
	-rm -f matrix.o mmul.o matrix_mul

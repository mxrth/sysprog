CC = clang

CFLAGS = -g3 -Wall -Wextra --std=c99 --pedantic

all: matrixgen matrixop

matrixgen: matrixgen_main.o matrix_gen.o matrix_alloc.o
	$(CC) -o $@ $^

matrix_gen.o: matrix_gen.c matrix.h

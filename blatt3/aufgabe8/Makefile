CC = clang


CFLAGS = -g3 -Wall -Wextra --std=c99 --pedantic

OBJECTS = matrixgen_main.o matrix_gen.o matrix_alloc.o matrix_io.o main.o

EXECUTABLES = matrixgen matrixop

all: matrixgen matrixop

matrixgen: matrixgen_main.o matrix_gen.o matrix_alloc.o matrix_io.o
	$(CC) -o $@ $^

matrixop: matrix_alloc.o matrix_io.o main.o
	$(CC) -o $@ $^

matrix_gen.o: matrix_gen.c matrix.h

matrix_alloc.o: matrix_alloc.c

matrix_io.o: matrix_io.c matrix.h

main.o: *.c *.h

.PHONY: clean

clean:
	-rm -rf $(OBJECTS) $(EXECUTABLES)

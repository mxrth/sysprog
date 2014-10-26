CC = clang


CFLAGS = -g3 -Wall -Wextra --std=c99 --pedantic

OBJECTS = matrixgen_main.o matrix_gen.o matrix_alloc.o
EXECUTABLES = matrixgen matrixop

#all: matrixgen matrixop

matrixgen: matrixgen_main.o matrix_gen.o matrix_alloc.o matrix_io.o
	$(CC) -o $@ $^

matrix_gen.o: matrix_gen.c matrix.h

matrix_alloc.o: matrix_alloc.c

.PHONY: clean

clean:
	-rm -rf $(OBJECTS) $(EXECUTABLES)

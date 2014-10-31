CC := clang

override CFLAGS += -g3 -Wall -Wextra --std=c99 --pedantic -pg

OBJECTS := matrixgen_main.o matrix_gen.o matrix_alloc.o matrix_io.o main.o matrix_ops.o matrixop_main.o

EXECUTABLES := matrixgen matrixop

.PHONY: all
all: matrixgen matrixop

matrixgen: matrixgen_main.o matrix_gen.o matrix_alloc.o matrix_io.o
	$(CC) $(CFLAGS) -o $@ $^

matrixop: matrixop_main.o matrix_alloc.o matrix_io.o matrix_ops.o
	$(CC) $(CFLAGS) -o $@ $^

matrix_gen.o: matrix_gen.c matrix.h

matrix_alloc.o: matrix_alloc.c matrix.h

matrix_ops: matrix_ops.c matrix.h

matrix_io.o: matrix_io.c matrix.h

matrixop_main.o: matrixop_main.c matrix.h

main.o: *.c *.h

.PHONY: clean

clean:
	-rm -rf $(OBJECTS) $(EXECUTABLES)

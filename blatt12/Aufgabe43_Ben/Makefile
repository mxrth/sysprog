CC := clang

override CFLAGS += -g3 -Wall -Wextra --std=c99 --pedantic

OBJECTS := matrix_alloc.o matrix_io.o main.o matrix_ops.o

EXECUTABLES := matrix_threads

.PHONY: all
all: matrix_threads

matrix_threads: main.o matrix_alloc.o matrix_io.o matrix_ops.o
	$(CC) $(CFLAGS) -o $@ $^

matrix_alloc.o: matrix_alloc.c matrix.h

matrix_ops.o: matrix_ops.c matrix.h

matrix_io.o: matrix_io.c matrix.h

main.o: *.c *.h

.PHONY: clean

clean:
	-rm -rf $(OBJECTS) $(EXECUTABLES)

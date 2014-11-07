CC := clang

override CFLAGS += -g3 -Wall -Wextra --std=c99 --pedantic -pg

OBJECTS := main.o input.o

EXECUTABLES := client

all: client

client: $(OBJECTS)
	$(CC) -o $@ $^

main.o: *.c *.h

.PHONY: all clean

clean:
	-rm -rf $(OBJECTS) $(EXECUTABLES)

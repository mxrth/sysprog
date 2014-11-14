CC := gcc

override CFLAGS += -g3 -Wall -Wextra --std=c99 --pedantic

EXECUTABLE := client.exe

OBJECTS := client.o

client.exe: client.o
	$(CC) $(CFLAGS) -o client.exe $(OBJECTS)

client.o: client.c util.h
	$(CC) $(CFLAGS) -c client.c util.h
	
.PHONY: all clean

clean:
	-rm -rf $(OBJECTS) $(EXECUTABLE)

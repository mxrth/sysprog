CC := gcc

override CFLAGS += -g3 -Wall -Wextra --std=c99 --pedantic

EXECUTABLE := client.exe

OBJECTS := client.o unp_readline.o

client.exe: client.o unp_readline.o
	$(CC) $(CFLAGS) -o client.exe $(OBJECTS)

client.o: client.c util.h 
	$(CC) $(CFLAGS) -c client.c 

unp_readline.o: unp_readline.c unp_readline.h
	$(CC) $(CFLAGS) -c unp_readline.c 
	
.PHONY: all clean

clean:
	-rm -rf $(OBJECTS) $(EXECUTABLE)

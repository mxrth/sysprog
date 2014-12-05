CC := clang

override CFLAGS += -g3 -Wall -Wextra --std=c99 --pedantic

EXECUTABLE := server
OBJECTS := server.o transaction.o unp_readline.o

server: server.o transaction.o unp_readline.o

server.o: server.c util.h unp_readline.c unp_readline.h transaction.o
	$(CC) $(CFLAGS) -c -o server.o server.c

unp_readline.o: unp_readline.h unp_readline.c

transaction.o: transaction.c transaction.h unp_readline.h


.PHONY: all clean

clean:
	-rm -rf $(OBJECTS) $(EXECUTABLE)

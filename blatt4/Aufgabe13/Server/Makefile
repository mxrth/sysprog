CC := clang

override CFLAGS += -g3 -Wall -Wextra --std=c99 --pedantic

EXECUTABLE := server 

server: server.c util.h
	$(CC) $(CFLAGS) -o server server.c

.PHONY: all clean

clean:
	-rm -rf $(OBJECTS) $(EXECUTABLE)

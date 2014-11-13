CC := clang

override CFLAGS += -g3 -Wall -Wextra --std=c99 --pedantic

EXECUTABLE := tcpserver

OBJECTS := tcpserver.o sock.o 

all: $(EXECUTABLE)

sock.o: sock.c

tcpserver.o: tcpserver.c

tcpserver: $(OBJECTS)
	$(CC) $(CFLAGS) -o tcpserver $(OBJECTS)  

.PHONY: all clean

clean:
	-rm -rf $(OBJECTS) $(EXECUTABLE)

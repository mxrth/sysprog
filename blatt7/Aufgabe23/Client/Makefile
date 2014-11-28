CC := clang

override CFLAGS += -g3 -Wall -Wextra --std=c99 --pedantic

EXECUTABLE := tcpchatclient

OBJECTS := main.o sockettools.o tcpchatclient.o

tcpchatclient:  $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

main.o: main.c sockettools.h tcpchatclient.h

sockettools.o: sockettools.c sockettools.h

tcpchatclient.o: tcpchatclient.c tcpchatclient.h

.PHONY: all clean

clean:
	-rm -rf $(OBJECTS) $(EXECUTABLE)

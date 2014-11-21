CC := clang

override CFLAGS += -g3 -Wall -Wextra --std=gnu99 --pedantic

EXECUTABLE := bankclient

OBJECTS := main.o sockettools.o bankclient.o

all: bankclient

bankclient: $(OBJECTS) 
	$(CC) $(CFLAGS) -o bankclient $(OBJECTS) 

main.o: main.c sockettools.h bankclient.h util.h

sockettools.o: sockettools.c sockettools.h util.h

bankclient.o: bankclient.c bankclient.h util.h

.PHONY: all clean

clean:
	-rm -rf $(OBJECTS) $(EXECUTABLE)

CC := clang

override CFLAGS += -g3 -Wall -Wextra --std=gnu99 --pedantic

EXECUTABLE := tcpchatserver 

tcpchatserver: TCPChatServer.c util.h unp_readline.c unp_readline.h
	$(CC) $(CFLAGS) -o tcpchatserver TCPChatServer.c unp_readline.c

.PHONY: all clean

clean:
	-rm -rf $(OBJECTS) $(EXECUTABLE)

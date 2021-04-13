CC = gcc
CFLAGS = -lwsock32

.PHONY: all clean

all: server client

server: server.c
	$(CC) server.c $(CFLAGS) -o server.exe

client: client.c
	$(CC) client.c $(CFLAGS) -o client.exe

clean:
	del client.exe server.exe

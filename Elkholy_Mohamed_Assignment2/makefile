CC = gcc
CFLAGS = -Wall -Wextra

all: server client 

server: server.c
	$(CC) $(CFLAGS) -o server server.c -lrt

client: client.c
	$(CC) $(CFLAGS) -o client client.c -lrt

clean:
	rm -f server client

.PHONY: all clean
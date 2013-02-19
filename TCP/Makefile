# Makefile

SH = bash
CFLAGS = -g
LDFLAGS = -lm
CC = gcc

all: server client

# Write Makefile rules to compile the client and server program,
server: server.o
	$(CC) $(LDFLAGS) $^ -o $@
client: client.o
	$(CC) $(LDFLAGS) $^ -o $@
server.o: serverTcp.c ../Def.h
	$(CC) -c $(CFLAGS) $< -o $@
client.o: clientTcp.c ../Def.h
	$(CC) -c $(CFLAGS) $< -o $@
.PHONY: clean lint test

clean:
	rm -rf *.o
	rm -rf server
	rm -rf client

lint:
	for f in *.c; do echo $$f; splint -standard $$f; done;


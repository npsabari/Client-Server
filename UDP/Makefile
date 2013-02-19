# Makefile

SH = bash
CFLAGS = -g
LDFLAGS = -lm
CC = gcc

all: server client serverWrap

# Write Makefile rules to compile the client and server program,
server: server.o BSTree.o
	$(CC) $(LDFLAGS) $^ -o $@
client: client.o
	$(CC) $(LDFLAGS) $^ -o $@
serverWrap: serverWrap.o BSTree.o
	$(CC) $(LDFLAGS) $^ -o $@
server.o: serverUdp.c ../Def.h
	$(CC) -c $(CFLAGS) $< -o $@
serverWrap.o: serverWrapUdp.c ../Def.h
	$(CC) -c $(CFLAGS) $< -o $@
client.o: clientUdp.c ../Def.h
	$(CC) -c $(CFLAGS) $< -o $@
BSTree.o: BSTree/BSTree.c BSTree/BSTree.h
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean lint test

clean:
	rm -rf *.o
	rm -rf server
	rm -rf client
	rm -rf serverWrap 

lint:
	for f in *.c; do echo $$f; splint -standard $$f; done;


CC=gcc
CFLAGS=-std=c11 -Wall

all:
	$(CC) $(CFLAGS) -lncurses dirfncs.c main.c -o le3v1nb
clean:
	rm le3v1nb



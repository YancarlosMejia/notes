CC=gcc
CFLAGS=-Wall -ggdb

.PHONY: sploit1.c, sploit2.c, sploit3.c, sploit4.c

all: sploit1 sploit2 sploit3 sploit4

sploit1: sploit1.c
	$(CC) $(CFLAGS) sploit1.c -o sploit1

sploit2: sploit2.c
	$(CC) $(CFLAGS) sploit2.c -o sploit2

sploit3: sploit3.c
	$(CC) $(CFLAGS) sploit3.c -o sploit3

sploit4: sploit4.c
	$(CC) $(CFLAGS) sploit4.c -o sploit4

copy:
	scp * ugster:/home/lajaneck/uml/share
# makefile pour TP2 projet 2 C
# MECHERIKI Charles
# MAURICE Valentin

CC=gcc
CFLAGS = -W -Wall -g -std=gnu99 -D_GNU_SOURCE

all: tp3_a

tp3_a: tp3_a.o pile.o tp2_a.o json_tree.o
	$(CC) $(CFLAGS) -o tp3_a tp3_a.o pile.o tp2_a.o json_tree.o

tp3_a.o: tp3_a.c pile.h tp2_a.h json_tree.h
	$(CC) $(CFLAGS) -o tp3_a.o -c tp3_a.c

json_tree.o: json_tree.c
	$(CC) $(CFLAGS) -o json_tree.o -c json_tree.c

tp2_a.o: tp2_a.c
	$(CC) $(CFLAGS) -o tp2_a.o -c tp2_a.c

pile.o: pile.c
	$(CC) $(CFLAGS) -o pile.o -c pile.c
	

# .PHONY: clean

clean:
	rm -vf *.o

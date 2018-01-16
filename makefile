# makefile pour TP2 projet 2 C
# MECHERIKI Charles
# MAURICE Valentin

CC=gcc
CFLAGS = -W -Wall -g -std=gnu99 -D_GNU_SOURCE
EXEC=tp3_a
all:$(EXEC)

$(EXEC): tp3_a.o pile.o tp2_a.o json_tree.o
	gcc $(CCFLAGS) -o  $(EXEC) tp3_a.o pile.o tp2_a.o json_tree.o

json_tree: json_tree.c
	$(CC)  $(CCFLAGS) -o json_tree.o -c json_tree.c

tp2_a.o: tp2_a.c
	$(CC)  $(CCFLAGS) -o tp2_a.o -c tp2_a.c

pile.o: pile.c
	$(CC)  $(CCFLAGS) -o pile.o -c pile.c

tp3_a.o: tp3_a.c pile.h tp2_a.h json_tree.h
	$(CC)  $(CCFLAGS) -o tp3_a.o -c tp3_a.c

# .PHONY: clean

clean:
	rm -vf *.o

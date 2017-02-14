CC=gcc

CFLAGS=-o 173proj -w
all:
	$(CC) $(CFLAGS) IntSet.c LinkedList.c nfa.c dfa.c conversion.c Driver.c
clean:
	rm -rf *o 173proj

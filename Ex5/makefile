CC = gcc
CFLAGS = -Wall -pg

all: brute_force improvement kadanes_alg

brute_force: brute_force.c
	$(CC) $(CFLAGS) -o brute_force brute_force.c

improvement: improvement.c
	$(CC) $(CFLAGS) -o improvement improvement.c

kadanes_alg: kadanes_alg.c
	$(CC) $(CFLAGS) -o kadanes_alg kadanes_alg.c

.PHONY: clean all

clean:
	rm -f brute_force improvement kadanes_alg

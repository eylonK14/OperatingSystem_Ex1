CC = gcc
FLAGS = -g

all: Poisson

Poisson: poisson.c 
	$(CC) $(FLAGS) -o Poisson poisson.c -lm

.PHONY: clean all

clean: 
	rm -f Poisson
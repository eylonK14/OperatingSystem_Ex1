CC = gcc
CFLAGS = -Wall -g -fprofile-arcs -ftest-coverage

all = main

main: main.c
	$(CC) $(CFLAGS) -o main main.c

.PHONY: clean all

clean:
	rm -f main *.gcov *.gcda *.gcno

CC = gcc
CFLAGS = -Wall -g

all: add2PB findPhone

add2PB: add2PB.c
	$(CC) $(CFLAGS) -o add2PB add2PB.c

findPhone: findPhone.c
	$(CC) $(CFLAGS) -o findPhone findPhone.c

.PHONY: clean all

clean:
	rm -f add2PB findPhone
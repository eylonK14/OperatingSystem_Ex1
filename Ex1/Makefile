CC = gcc
FLAGS = -g


all: division_by_zero stack_overflow undefined_memory

division_by_zero: division_by_zero.c
	$(CC) $(FLAGS) -o division_by_zero division_by_zero.c

stack_overflow: stack_overflow.c
	$(CC) $(FLAGS) -o stack_overflow stack_overflow.c

undefined_memory: undefined_memory.c
	$(CC) $(FLAGS) -o undefined_memory undefined_memory.c

.PHONY: clean all

clean:
	rm division_by_zero stack_overflow undefined_memory
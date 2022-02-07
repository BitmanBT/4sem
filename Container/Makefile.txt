CC = gcc
CFLAGS = -Wall -Wextra

all: test

list.o: list.c
	$(CC) $(CFLAGS) list.c -c -o list.o

test_main.o: test_main.c
	$(CC) $(CFLAGS) test_main.c -c -o test_main.o

test: list.o test_main.o
	$(CC) $(CFLAGS) list.o test_main.o -o test

clean:
	rm *.o
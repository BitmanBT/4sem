CC = gcc
CFLAGS = -Wall -Wextra

all: $(cont)

vector.o: vector.c
	$(CC) $(CFLAGS) vector.c -c -o vector.o

test_sort_vector.o: test_sort_vector.c
	$(CC) $(CFLAGS) test_sort_vector.c -c -o test_sort_vector.o

vector: vector.o test_sort_vector.o
	$(CC) $(CFLAGS) vector.o test_sort_vector.o -o vector

test_main_vector.o: test_main_vector.c
	$(CC) $(CFLAGS) test_main_vector.c -c -o test_main_vector.o

main_vector: vector.o test_main_vector.o
	$(CC) $(CFLAGS) vector.o test_main_vector.o -o main_vector

list.o: list.c
	$(CC) $(CFLAGS) list.c -c -o list.o

test_sort_list.o: test_sort_list.c
	$(CC) $(CFLAGS) test_sort_list.c -c -o test_sort_list.o

list: list.o test_sort_list.o
	$(CC) $(CFLAGS) list.o test_sort_list.o -o list

test_main_list.o: test_main_list.c
	$(CC) $(CFLAGS) test_main_list.c -c -o test_main_list.o

main_list: list.o test_main_list.o
	$(CC) $(CFLAGS) list.o test_main_list.o -o main_list

clean:
	rm *.o
	rm list
	rm vector
	rm main_list
	rm main_vector
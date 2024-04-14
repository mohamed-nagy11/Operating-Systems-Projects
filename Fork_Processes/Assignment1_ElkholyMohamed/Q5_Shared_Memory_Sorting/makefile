CC = gcc
CFLAGS = -Wall -Wextra

all: shared_memory ascending_sort descending_sort

shared_memory: shared_memory.c
	$(CC) $(CFLAGS) -o shared_memory shared_memory.c -lrt

ascending_sort: ascending_sort.c
	$(CC) $(CFLAGS) -o ascending_sort ascending_sort.c -lrt

descending_sort: descending_sort.c
	$(CC) $(CFLAGS) -o descending_sort descending_sort.c -lrt

clean:
	rm -f shared_memory ascending_sort descending_sort

.PHONY: all clean
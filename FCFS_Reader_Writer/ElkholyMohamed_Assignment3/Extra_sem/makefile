CC = gcc
CFLAGS = -Wall -pthread

all: Extrasem_exe

Extrasem_exe: Extra_sem.o
	$(CC) $(CFLAGS) -o Extrasem_exe Extra_sem.o -lrt

Extra_sem.o: Extra_sem.c
	$(CC) $(CFLAGS) -c Extra_sem.c

clean:
	rm -f Extrasem_exe Extra_sem.o

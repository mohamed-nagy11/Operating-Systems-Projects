CC=gcc
CFLAGS=-lpthread -lrt
OBJ=Assign3_sem.o

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

assign3sem_exe: $(OBJ)
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f assign3sem_exe

CC=gcc
CFLAGS=-I.
OBJ=helloworld.o

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

helloworld: $(OBJ)
	$(CC) -o $@ $< $(CFLAGS)
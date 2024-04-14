CC=gcc
CFLAGS=-I.
OBJ=cat.o 

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

cat: $(OBJ)
	$(CC) -o $@ $< $(CFLAGS)
	
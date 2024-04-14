CC=gcc
CFLAGS=-I.
OBJ=echo.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

echo: $(OBJ)
	$(CC) -o $@ $< $(CFLAGS)
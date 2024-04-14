CC = gcc
CFLAGS = -pthread -Wall

all: reader_writer

reader_writer: reader_writer.o
	$(CC) $(CFLAGS) -o reader_writer reader_writer.o

reader_writer.o: reader_writer.c
	$(CC) $(CFLAGS) -c reader_writer.c

clean:
	rm -f reader_writer reader_writer.o

CC = gcc
CFLAGS = -Wall -g

all: fifo_read fifo_write

fifo_read: fifo_read.c
	$(CC) $(CFLAGS) -o $@ $<

fifo_write: fifo_write.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f fifo_read fifo_write

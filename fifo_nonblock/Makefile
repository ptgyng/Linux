CC := gcc
CFLAGS := -Wall -g
TARGETS := fifo_read fifo_write

all: $(TARGETS)

fifo_read: fifo_read.c
	$(CC) $(CFLAGS) -o $@ $<

fifo_write: fifo_write.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f myfifo

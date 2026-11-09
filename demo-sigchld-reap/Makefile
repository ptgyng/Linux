CC = gcc
CFLAGS = -Wall -g
TARGET = sigchld_reap

all: $(TARGET)

$(TARGET): sigchld_reap.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)

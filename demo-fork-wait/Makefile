CC = gcc
CFLAGS = -Wall -g
TARGET = demo_fork_wait

all: $(TARGET)

$(TARGET): demo_fork_wait.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)

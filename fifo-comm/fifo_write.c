#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <fifo_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_WRONLY);
    if (fd < 0)
    {
        perror("open fifo write");
        exit(EXIT_FAILURE);
    }

    const char *msg = "hello fifo, independent process communication";
    write(fd, msg, strlen(msg));

    printf("write is over\n");
    close(fd);

    return 0;
}

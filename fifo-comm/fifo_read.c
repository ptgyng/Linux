#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUF_SIZE 128

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <fifo_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("open fifo read");
        exit(EXIT_FAILURE);
    }

    char buf[BUF_SIZE];
    ssize_t n;
    while ((n = read(fd, buf, BUF_SIZE - 1)) > 0)
    {
        buf[n] = '\0';
        printf("read: %s\n", buf);
    }

    // 所有写端close后，read返回0，退出循环
    if (n == 0)
    {
        printf("fifo write side all closed, read EOF\n");
    }
    else
    {
        perror("read");
    }

    close(fd);
    return 0;
}

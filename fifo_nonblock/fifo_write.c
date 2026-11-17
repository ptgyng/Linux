#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s fifo_name\n", argv[0]);
        exit(-1);
    }

    // 保证FIFO存在
    if (mkfifo(argv[1], 0664) < 0)
    {
        if (errno != EEXIST)
        {
            perror("mkfifo");
            exit(-1);
        }
    }

    // 写端非阻塞打开
    int fd = open(argv[1], O_WRONLY | O_NONBLOCK);
    if (fd < 0)
    {
        perror("open write");
        exit(-1);
    }

    char msg[] = "hello fifo nonblock test";
    ssize_t ret = write(fd, msg, strlen(msg));
    if (ret < 0)
    {
        perror("write");
    }
    else
    {
        printf("write success, send %zd bytes\n", ret);
    }

    close(fd);
    return 0;
}

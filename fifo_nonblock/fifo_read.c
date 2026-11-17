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

    // 先创建FIFO，存在也没关系
    if (mkfifo(argv[1], 0664) < 0)
    {
        if (errno != EEXIST)
        {
            perror("mkfifo");
            exit(-1);
        }
    }

    // 先阻塞open，打开之后再设置非阻塞，避开刚才的坑
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("open read");
        exit(-1);
    }
    fcntl(fd, F_SETFL, O_NONBLOCK);

    char buf[128] = {0};
    ssize_t ret;
    while (1)
    {
        ret = read(fd, buf, sizeof(buf) - 1);
        if (ret < 0)
        {
            if (errno != EAGAIN && errno != EWOULDBLOCK)
            {
                perror("read");
                break;
            }
            printf("no data...\n");
            sleep(1);
            continue;
        }
        else if (ret == 0)
        {
            printf("write side close\n");
            break;
        }
        buf[ret] = '\0';
        printf("read: %s\n", buf);
    }

    close(fd);
    return 0;
}

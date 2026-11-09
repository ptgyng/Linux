/**
 * @file sys_demo.c
 * @brief Linux系统调用实验：文件IO open/write/read/lseek
 * @details 功能：创建文件，写入字符串，移动文件偏移，读取内容并打印到终端
 * @author xxx
 * @date 2026-09-08
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    // 待写入文件的缓冲区
    char w_buf[] = "Hello Linux Syscall";
    // 读取数据的接收缓冲区
    char r_buf[64] = {0};
    int fd;         // 文件描述符
    ssize_t ret;    // 系统调用返回值，保存read读取到的字节数

    /*
     * open：打开/创建文件
     * O_RDWR：读写模式；O_CREAT：文件不存在则新建；O_TRUNC：文件存在则清空内容
     * 0644：文件权限，所有者读写，组和其他用户只读
     */
    fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd == -1)
    {
        perror("open failed");  // 打印系统错误信息
        return -1;
    }

    /* write系统调用：将缓冲区数据写入打开的文件 */
    if(write(fd, w_buf, sizeof(w_buf)-1) == -1)
    {
        perror("write failed");
        close(fd);   // 出错必须关闭文件描述符，防止资源泄漏
        return -1;
    }

    /* lseek：移动文件读写指针，SEEK_SET代表从文件头部开始，偏移量0，回到文件起始位置 */
    lseek(fd, 0, SEEK_SET);

    /* read系统调用：从文件读取数据到r_buf缓冲区 */
    ret = read(fd, r_buf, sizeof(r_buf)-1);
    if(ret == -1)
    {
        perror("read failed");
        close(fd);
        return -1;
    }

    /* write到标准输出(STDOUT_FILENO=1)，把读到的内容打印在终端 */
    write(STDOUT_FILENO, r_buf, ret);

    close(fd);  // 关闭文件，释放文件描述符资源
    return 0;
}

/*
 * @brief Linux 匿名管道串联实验
 * 模拟 shell 命令：ls -l | grep txt | wc -l
 * 两根匿名管道，三个进程，dup2 重定向标准输入输出
 *
 * 知识点：
 * 1. pipe() 创建匿名管道，fd[0]读端，fd[1]写端
 * 2. fork() 创建子进程，亲缘进程通信
 * 3. dup2() 文件描述符重定向
 * 4. 字节流管道，闲置fd必须close，否则无法收到EOF阻塞
 *
 * 编译：make
 * 运行：./learndup21_4
 * 环境：Ubuntu Linux / gcc
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    // pipe1: ls -> grep
    int pipe1[2];
    // pipe2: grep -> wc
    int pipe2[2];

    pipe(pipe1);
    pipe(pipe2);

    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        // 子进程1：ls -l
        close(pipe1[0]);       // 不用pipe1读端
        close(pipe2[0]);       // pipe2全部不用
        close(pipe2[1]);
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[1]);
        execlp("ls", "ls", "-l", NULL);
    }

    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        // 子进程2：grep txt
        close(pipe1[1]);       // 不用pipe1写端
        close(pipe2[0]);       // 不用pipe2读端
        dup2(pipe1[0], STDIN_FILENO);
        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe1[0]);
        close(pipe2[1]);
        execlp("grep", "grep", "txt", NULL);
    }

    pid_t pid3 = fork();
    if (pid3 == 0)
    {
        // 子进程3：wc -l
        close(pipe1[0]);
        close(pipe1[1]);       // pipe1全部不用
        close(pipe2[1]);       // 不用pipe2写端
        dup2(pipe2[0], STDIN_FILENO);
        close(pipe2[0]);
        execlp("wc", "wc", "-l", NULL);
    }

    // 父进程：关闭所有管道fd，等待三个子进程回收
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    return 0;
}

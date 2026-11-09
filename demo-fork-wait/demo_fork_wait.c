#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

/*
归档Demo：fork + exit/_exit + wait/waitpid
编译：gcc demo_fork_wait.c -o demo_fork_wait
运行：./demo_fork_wait
*/
int main(void)
{
    pid_t pid;
    int status;

    printf("【父进程】main start, father pid = %d\n", getpid());

    pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // ====== 子进程区域 ======
        printf("【子进程】son pid = %d, parent ppid = %d\n", getpid(), getppid());

        // 测试1：exit 会刷新缓冲区，执行退出处理
        exit(8888);
        // 测试2：_exit(8888); 系统调用，不做用户态清理
    }
    else
    {
        // ====== 父进程区域 ======
        printf("【父进程】fork成功，子进程pid=%d，开始wait阻塞等待\n", pid);

        // wait 阻塞等待子进程
        // wait(&status);

        // waitpid版本，等价上面wait，打开下面注释即可切换
        waitpid(pid, &status, 0);

        printf("【父进程】捕获到子进程退出\n");
        if (WIFEXITED(status))
        {
            printf("子进程正常退出，退出码(低8位)=%d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("子进程异常退出\n");
        }
    }

    return 0;
}

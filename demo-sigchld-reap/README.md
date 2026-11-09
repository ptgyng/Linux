# demo-sigchld-reap
> Linux SIGCHLD信号异步回收僵尸进程 Demo
## 核心知识点
1. SIGCHLD：子进程终止时，内核自动发送给父进程的信号
2. sigaction 注册信号处理函数，`SA_RESTART` 自动重启被信号打断的系统调用
3. `waitpid(-1, NULL, WNOHANG)`：非阻塞方式回收子进程
4. while循环调用waitpid：信号存在合并丢失现象，一次SIGCHLD可能对应多个退出子进程，需要循环全部回收

## 编译运行
```bash
make
./sigchld_reap

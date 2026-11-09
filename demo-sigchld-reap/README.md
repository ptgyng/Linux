# demo-sigchld-reap
> Linux SIGCHLD信号异步回收僵尸进程 Demo
## 核心知识点
1. SIGCHLD：子进程终止时内核发送给父进程的信号
2. sigaction 注册信号处理函数，SA_RESTART 自动重启被信号中断的系统调用
3. waitpid(-1, NULL, WNOHANG) 非阻塞回收
4. while循环调用waitpid：信号会合并，一次信号可能对应多个已退出子进程，必须循环收干净
## 编译运行
```bash
make
./sigchld_reap

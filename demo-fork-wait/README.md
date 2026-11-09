# demo-fork-wait
> 个人Linux系统编程归档Demo

## 核心知识点
1. fork：一次调用两次返回，创建子进程
2. exit（C库函数） vs _exit（系统调用）区别
3. wait / waitpid 阻塞回收子进程
4. 宏：WIFEXITED、WEXITSTATUS 获取子进程退出状态

## 编译运行
```bash
make
./demo_fork_wait

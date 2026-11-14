# Linux 匿名管道实验：多进程管道串联
## 项目简介
C语言实现Linux匿名管道（pipe），串联3个进程，模拟shell命令：
```bash
ls -l | grep txt | wc -l

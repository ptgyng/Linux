# Linux C 进程与信号 Demo 仓库
本仓库存放Linux系统编程学习示例，每个文件夹为独立Demo，配套源码、Makefile与说明文档，适合学习、面试展示。

## 📂 Demo目录
- **demo-fork-wait**：fork创建子进程 + exit/_exit + wait/waitpid阻塞回收
- **demo-sigchld-reap**：SIGCHLD信号异步回收僵尸进程，fork-wait进阶示例

## 🛠️ 编译运行说明
进入对应demo文件夹：
```bash
make          # 编译程序
./xxx         # 运行
make clean    # 删除编译产物

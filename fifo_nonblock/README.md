## 编译运行
```bash
make
# 终端1 启动读端
./fifo_read myfifo
# 终端2 启动写端
./fifo_write myfifo

# 清理
make clean

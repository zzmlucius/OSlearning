## 管道程序为什么要求每个进程关闭不用的管道端

example:
```c
int p[2];
char *argv[2];
argv[0] = "wc";
argv[1] = 0;
pipe(p);
if(fork() == 0) {
    close(0);
    dup(p[0]);     //stdin -> pipe read end
    close(p[0]);   
    close(p[1]);   //我们讨论的重点在这。
    exec("/bin/wc", argv);
} else {
    write(p[1], "hello world\n", 12);
    close(p[0]);
    close(p[1]);
}
```

### 首先理解read的工作机制 和 **管道的特性**
- 1.wc()里面有一个循环判断，大概是while((n = read()) > 0)。
- 2.read()返回0的时机随读取对象变化，如果是普通文件，读到文件末尾(EOF)，如果是管道：**所有写端都关闭且管道内没有残留数据**(read的行为根据对象变化)
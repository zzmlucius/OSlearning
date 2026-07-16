## HOW OS redirect the IO and File Descriptor

### File Descriptor
内核再PCB中维护了一个FD Table：
0 -> stdin (默认键盘)
1 -> stdout(默认终端)
2 -> stderr(默认终端)
...

### redirect 例子

```c
int main()
{
    int pid;
    if(pid == 0) { //如果是子进程
        close(1);  //关闭stdout，即1 -> stdout(终端) 变成 1 -> 空
        open("output.txt", O_WRONLY|O_CREATE); //unix的特性是返回最小可用的文件描述符那么1 -> output.txt。

        char *argv[] = { "echo", "this", "is", "redirected", "echo", 0 };
        exec("echo", argv);
        printf("exec failed!\n");
        exit(1);
    }
    else {
        wait((int*)0);
    }
    exit(0);
}
```

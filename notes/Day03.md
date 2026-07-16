## 1.syscall()

### 系统调用是由一段汇编代码，一段C代码构成的。

汇编部分重点:1.保存系统调用号2.ecall(告诉CPU我要进入操作系统)使操作系统陷入内核

C代码:1.trap.c 2.syscall()按照系统调用号调用相应的系统调用。

比如:write() -> asm(ecall) -> 进入内核 -> syscall() -> 按照系统调用号调用sys_write()

## 2.三个进程API：fork() exec() wait()

### 一个经典例子:exec()

//exec.c: replace a process with an executable file

```c
int main()
{
    char *argv[] = { "echo", "this", "is", "echo", 0 };

    exec("echo", argv);

    printf("exec failed!\n");

    exit(0);
}
```

### 解释
1.argv是一个指针数组,所以其实是有5个指针指向了这一些字符串。
2.exec("echo", argv) 表示将当前进程替换成echo文件中的代码。
3.替换之后进入到int main(int argc, int * argv) 第一个放程序名，第二个放参数。

另一个fork and wait的例子:
#include "user/user.h"

### forkexec.c: fork exec and wait
```c
int main() 
{
    int pid, status;
    pid = fork(); //创建一个子进程，返回pid
    if(pid < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    if(pid == 0){ //注意:fork系统调用返回后,父子进程都是从这行开始,
        char * argv[] = { "echo", "THIS", "IS", "ECHO",0 };
        exec("echo", argv) ;
        printf("exec failed!\n");
        exit(1);}
    else {
        printf("parent waiting\n");
        wait(&status);
        printf("the child exited with status %d\n", status);
        exit(0);
    } 
}
```

### 解释
0.什么是PCB process control block ,是一个维护在内核的数据结构，kernel为每个进程都维护了一个
1.fork是两个独立的进程
2.exit()与wait()之间的通信：
1.不是直接通信，而是通过 PCB（进程控制块）传递信息。
2.子进程运行完了之后调用exit(退出码)进入内核，proc->state = zombie,内核记录退出码，此时PCB还在。父进程wait(&status)ecall进入内核后sys_wait开始检查所有孩子发现其中一个state = zombie，内核将退出码复制到父进程user态的status，最后释放PCB。

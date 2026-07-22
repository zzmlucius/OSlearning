## context switch 和 syscall 的时间开销

- context switch大概是2500 ~ 3000 CPU cycle。

- syscall 大概是320个 CPU cycle。




## Qemu + gdb远程调试xv6的启动
- 0.kernel.ld定义了内核是如何被加载的，规定_entry,.data,.bss等放在哪里
- 1.将kernel加载到内存。
- 2.跳转到0x80000000(_entry)，在CPU上建立内核栈，为后面运行C代码做准备。
- 3.start()：从machine mode 切换到 supervisor mode
- 4.来到main.c,初始化操作系统
- 5.main.c中完成初始化后来到userinit()
- 6.userinit()中发生了第一次系统调用，通过sys_exec()执行init程序，init程序跑了第一个shell。


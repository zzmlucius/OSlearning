## Lecture3：OS organizatio and syscall
主要内容是将OS怎么抽象硬件，以及OS实现的overview.但是有一个重要的东西就是，xv66内核是怎么编译的。

## makefile and qemu makes the xv6 run
- 1.makefile会将所有.c文件编译成.s进而编译成.o文件。
- 2.链接器ld(GNU Linker)会将所有.o文件链接起来，会找函数，合并代码段因为比如fork.o会有自己的代码段，sched.o也会有自己的代码段。(普通C程序有main()，但是内核没有指定的入口所以ld还要设置一个入口)
- 3.分配地址
- 4.生成elf文件(例如vmlinux)
- 5.bootloader加载

## xv6 syscall()

xv6的系统调用是由一段汇编代码，一段C代码构成的。

汇编部分重点:1.保存系统调用号2.ecall 使操作系统陷入内核

C代码:1.trap.c 2.syscall()按照系统调用号调用相应的系统调用。

比如:write() -> asm(ecall) -> 进入内核 -> syscall() -> 按照系统调用号调用sys_write()

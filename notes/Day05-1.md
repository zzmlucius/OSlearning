## Context Switch

### Trap

#### 产生Trap有三种情况
- 系统调用
- 异常
- 中断

#### 发生Trap之后(RISC-V)
- 保存scause表示是哪种情况产生的Trap，CPU跳到stvec，里面保存了Trap Entry Address。也就是**CPU只负责跳到一个固定地址**。

- 刚陷入内核时，CPU寄存器还是用户程序的，待保存完整现场于内核栈之后(寄存器值保存到trapframe)，调用usertrap().

- 处理Trap()，每钟scause对应不同的处理代码，处理完后从内核栈恢复用户现场。


## In a word，Trap 是进入内核的入口，而上下文切换是内核处理 Trap 时可能发生的一件事情。



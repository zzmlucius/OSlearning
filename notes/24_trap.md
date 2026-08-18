# Trap 的调用与返回

```text
用户态 write() → ecall → uservec → usertrap() → syscall() → sys_write()

sys_write()
  ─ret/ra→ syscall()
  ─ret/ra→ usertrap()
  → prepare_return()
  ─ret/ra→ usertrap()
  ─ret/ra，a0=用户satp→ userret
  ─sret/sepc→ 用户态 ecall 的下一条指令
```

## ecall

执行 `ecall` 后：

- `sepc` 保存 `ecall` 的指令地址；
- `pc` 被设置为 `stvec` 中的地址；
- `satp` 不变；
- `SPIE = SIE`，随后 `SIE = 0`，关闭 S-mode 中断；
- `SPP` 记录 trap 前的特权级。用户态执行 `ecall` 时，`SPP = 0`。

`stvec` 中保存的是 trampoline 中 `uservec` 的运行时地址。

## uservec

进入 trampoline 后，`pc = uservec`。

```text
将用户 a0 暂存到 sscratch
→ a0 = TRAPFRAME
→ 保存用户寄存器
→ 将 sscratch 中原来的用户 a0 保存到 trapframe->a0
→ sp = 进程的内核栈顶
→ tp = kernel_hartid
→ t0 = usertrap 的地址
→ t1 = kernel_satp
→ satp = t1，切换到内核页表
→ jalr t0，进入 usertrap
```

trampoline : pc = uservec
a0 = trapframe
保存寄存器值
t0 = usertrap
t1 = kernel pagetable
ra = pc + 4
jalr t0
执行 `jalr t0` 时：

usertrap : 将kernelvec写入stvec，让此时中断走kerneltrap(), 而不是反复usertrap
sepc存到trapframe(内存中)
打开中断
```text
ra = jalr 后面一条指令的地址 = userret 的运行时地址
pc = t0 = usertrap 的地址
```

## usertrap

`usertrap()` 将 `kernelvec` 写入 `stvec`，让此时发生的中断进入 `kerneltrap()`，而不是再次进入 `usertrap()`。

随后：

```text
将 CPU 的 sepc 保存到 p->trapframe->epc
→ 如果是系统调用，p->trapframe->epc += 4，跳过 ecall
→ 打开中断
→ syscall()
```

## syscall

`syscall()` 从 `p->trapframe->a7` 取得系统调用编号，然后调用对应的系统调用函数：

```c
p->trapframe->a0 = syscalls[num]();
```

例如：

```text
syscall()
  → sys_write()
  ← sys_write() 使用 ra 返回 syscall()
  ← syscall() 使用 ra 返回 usertrap()
```

syscall : p -> trapframe -> a0 = sys_...()
系统调用的返回值最终保存在 `p->trapframe->a0` 中。

sys_..():
## prepare_return

syscall : 回到syscall(用ra)
`usertrap()` 调用 `prepare_return()`，为本进程下一次从用户态进入内核做准备：

usertrap : 回到usertrap(用ra)
```text
p->trapframe->kernel_satp   = 当前内核页表
p->trapframe->kernel_sp     = 当前进程的内核栈顶
p->trapframe->kernel_trap   = usertrap 的地址
p->trapframe->kernel_hartid = 当前 hart ID
stvec                       = uservec 的运行时地址
```

prepare_return() : 恢复trapframe中内核页表，uservec地址，usertrap地址为本进程下一次使用做准备
恢复内存中sepc到cpu sepc
同时，将 `p->trapframe->epc` 写入 CPU 的 `sepc`：

usertrap(): 回到usertrap(用ra)
satp = p -> pagetable
return satp(内存)
```c
w_sepc(p->trapframe->epc);
```

userret: 回到userret(用ra)
且a0 = 返回值satp(用户satp)
satp(cpu) = a0
a0 = TRAPFRAME
恢复所有寄存器
`prepare_return()` 使用 `ra` 返回 `usertrap()`。

sret
pc = sepc(回到ecall下一行)
SIE = SPIE
SPIE = 1 
SPP = 0
## usertrap 返回 userret

`usertrap()` 计算用户页表对应的 `satp`：

```c
uint64 satp = MAKE_SATP(p->pagetable);
return satp;
```

这里：

- `ra` 中保存着 `userret` 的运行时地址，因此 `usertrap()` 使用 `ret` 返回 `userret`；
- 返回值 `satp` 放在 `a0` 中，因此进入 `userret` 时，`a0 = 用户 satp`。

## userret

```text
satp = a0，切换到用户页表
→ a0 = TRAPFRAME
→ 从 trapframe 恢复用户寄存器
→ 最后恢复用户 a0
→ sret
```

执行 `sret` 时：

```text
pc   = sepc，回到 ecall 的下一条指令
当前特权级 = SPP（这里返回 U-mode）
SIE  = SPIE
SPIE = 1
SPP  = 0
```
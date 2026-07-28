## Lecture 1

### Design Purposes

Abstraction
Mutiplex
Isolation
Sharing
Security
Performance

### Focusing on the Kernel and Kernel API for User space.

Processes
Memmory allocate
Access Control

### API-Kernel
e.g. open() fork()
Always through syscall.

### QEMU
a hardware simulator, simulates the cpu...

### Tensions
Efficient - Abstract
Powerful  - Simple (API)
Flexible  - Secure

### Labs, the answers will be on piazza and website.(google)

xv6 RISC-V QEMU
为什么OS总是和CPU关联在一起，因为OS需要直接操作寄存器RAM，而每种架构的寄存器RAM有区别，也就是OS不能完全抽象CPU

question:为什么不能完全抽象出CPU，也就是无论.exe .elf他们已经直接对应(机器指令)
  


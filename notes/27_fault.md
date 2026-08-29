### 发生错误时(user or kernel)，寄存器和pc怎么变化

CPU(纯硬件行为)会将右边写入左边寄存器
- scause : 异常类型
- sepc   : 出错时指令地址
- stval  : 出错时访问的va
- sstatus: 陷入内核之前的状态
- pc     : stvec

---

sstatus:
- sstatus.SPP   <- 陷入前特权级
- sstatus.SPIE  <- sstatus.SIE
- sstatus.SIE   <- 0 (禁用S模式中断)
SPP用于判断陷阱来自用户还是内核

### 使用fault handler可以实现 “lazy行为”，提升并发和实时速度
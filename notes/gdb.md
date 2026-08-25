### 在page fault时会发生什么

**以写入错误为例**
当CPU MMU访问到PTE_V = 0或其它写入错误时，
CPU:
- scause : 记录异常类型
- sepc   : 存储出错指令地址
- stval  : 出错时的va
- sstatus: trap前状态

- pc -> stvec : 进入trap

---

### sstatus:
- sstatus.SPP   : 陷入前特权级(判断陷阱来自用户还是内核)
- sstatus.SPIE  : 存储sstatus.SIE
- sstatus.SIE   : 0 (禁用S模式中断)

---

### What we can do with Page Fault:
- Lazy allocation
- zero fill on demand
- COW
- Demand paging
- Page Eviction
- mmap
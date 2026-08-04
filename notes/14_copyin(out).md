## copyout() : 内核空间 -> 用户空间

### 以sys_info() 为例 --- 为什么不能用a0回传？

- 1.a0是一个64位寄存器，而struct sys_info 一共128位。
- 2.而struct sys_info *p虽然是64位，但是内核态的地址和用户态的地址之间通常有不同的映射，而且用户态不能访问内核态的地址。

question about syscall
why copy     : 1. a0设计为装整数状态码或地址 2. 64位寄存器太小
why copyout(): 1.地址空间不同 2.对象生命周期 3.安全隔离

copyout() 源码:
```c
int
copyout(pagetable_t pagetable, uint64 dstva, char *src, uint64 len) // (用户虚拟地址对应的物理页表，用户虚拟地址，源数据地址，数据长度)
{
  uint64 n, va0, pa0;
  pte_t *pte;

  while (len > 0) {
    va0 = PGROUNDDOWN(dstva);         找到一页的起始地址
    if (va0 >= MAXVA)
      return -1;

    pa0 = walkaddr(pagetable, va0);   核心:虚拟地址 -> 页表查询 -> 物理地址
    if (pa0 == 0) {
      if ((pa0 = vmfault(pagetable, va0, 0)) == 0) {
        return -1;
      }
    }

    pte = walk(pagetable, va0, 0);
    // forbid copyout over read-only user text pages.
    if ((*pte & PTE_W) == 0)
      return -1;

    n = PGSIZE - (dstva - va0);       这一页还能复制多少
    if (n > len)
      n = len;
    memmove((void *)(pa0 + (dstva - va0)), src, n); memmove只能操作当前地址空间***可直接访问***的地址

    len -= n;
    src += n;
    dstva = va0 + PGSIZE;
  }
  return 0;
}
```
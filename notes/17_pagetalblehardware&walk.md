## page table hardware and walk function

- 每个CPU核有一个satp寄存器，存着当前虚拟地址对应根页表(L2)的物理地址。
- 每个CPU核都有一个MMU，MMU可以自动通过虚拟地址和satp将虚拟地址翻译成物理地址。(硬件walk)
- TLB缓存，存储常用虚拟地址到物理地址之间的映射，避免了三级查找。
- walk function : 
```c
pte_t *
walk(pagetable_t pagetable, uint64 va, int alloc) // 寻址、创建新页表页、查询
{
  if (va >= MAXVA)
    panic("walk");

  for (int level = 2; level > 0; level--) {
    pte_t *pte = &pagetable[PX(level, va)];  // pagetable即PTE数组，PX(level, va)获得索引
    if (*pte & PTE_V) {
      pagetable = (pagetable_t)PTE2PA(*pte);
    } else {
      if (!alloc || (pagetable = (pde_t *)kalloc()) == 0) // alloc = 0表示只查询，缺页就返回 0
        return 0;                                         // alloc = 1表示缺页就分配
      memset(pagetable, 0, PGSIZE);
      *pte = PA2PTE(pagetable) | PTE_V;
    }
  }
  return &pagetable[PX(0, va)]; // 返回L0PTE所在地址
}
```
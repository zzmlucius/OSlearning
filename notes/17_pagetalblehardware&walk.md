## page table hardware and walk function

- 每个CPU核有一个satp寄存器，存着当前虚拟地址对应根页表(L2)的物理地址。
- 每个CPU核都有一个MMU，MMU可以自动通过虚拟地址和satp将虚拟地址翻译成物理地址。(硬件walk)
- walk function : 
```c
pte_t *
walk(pagetable_t pagetable, uint64 va, int alloc)
{
  if (va >= MAXVA)
    panic("walk");

  for (int level = 2; level > 0; level--) {
    pte_t *pte = &pagetable[PX(level, va)];
    if (*pte & PTE_V) {
      pagetable = (pagetable_t)PTE2PA(*pte);
    } else {
      if (!alloc || (pagetable = (pde_t *)kalloc()) == 0)
        return 0;
      memset(pagetable, 0, PGSIZE);
      *pte = PA2PTE(pagetable) | PTE_V;
    }
  }
  return &pagetable[PX(0, va)];
}
```
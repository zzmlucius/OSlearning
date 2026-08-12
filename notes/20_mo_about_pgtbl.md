## kalloc 与 mappages/walk

- 1. kaloc(): 找一块空闲的物理内存(freelist是物理内存链表)

- 2. mappages/walk: 将虚拟内存指向物理内存(已分配)

- 3. 内核页表在kvminit()时就已经创建好了。除了kvminit之外，内核在整个生命周期不会创建新的页表项

- 4. 页表建立的不是 "任意va -> 任意pa" 的映射，而是虚拟页 -> 物理页，页内偏移不便(offset)，这也解释了mappages()要求页对齐

- 5. 内核态调用kalloc可行是因为内核态虚拟地址与物理地址一一映射。
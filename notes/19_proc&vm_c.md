## 创建进程的重要代码

- kalloc : 从freelist获得一块空闲物理页
- kfree : 释放物理内存还给freelist
- mappages : 传入根页表地址pagetable, 待映射pa与va, 建立映射
- uvmunmap : 删除叶子映射, 按参数是否同时释放物理页
- uvmfree : 删除用户空间映射, 释放整张页表

- allocproc : 创建一个进程并分配好除用户内存之外的物理地址
- proc_pagetable : 将TRAMPOLINE, TRAPFRAME, USYSCALL映射到allocproc分配好的物理地址

**allocproc -> 分配好pa -> proc_pagetable -> 映射tp, tf, usys到pa**

- 如果allocproc失败，将调用freeproc(本质对进程各物理页kfree)
- 如果proc_pagetable失败，将调用uvmunmap解除映射
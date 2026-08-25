# kpgtbl per process

### 原因: 如果每个进程保存有一个内核页表副本，然后将用户页表也编入这个副本，这样cpu在K/U之间执行MMU walk的时候就不用更换页表不用flush TLB，用户态地址在内核态执行也不必walkaddr()而可以直接对va进行walk
---
### 几个纠正:
- 1.pc每一步都在使用MMU，无论是用户还是内核态
- 2.硬件MMU怎么能正确使用os(软件)动态建立的页表: risc-v Sv39协议规定了页表必须长啥样
- 3.中间页表也需要kalloc
- 4.scheduler运行在global内核页表，在scheduler上可以放心切换内核页表副本和global内核页表，因为scheduler不是运行在kernel stack(copies与global不同), 而是运行在一个global内核页表上就有的地址。
---
### 几个函数:
kvminit() kvmmake() kvminithart() scheduler() procinit() proc_mapstacks() 重新认识 kalloc() kfree()
- kvmmake: 建立内核页表映射
- kvminit: 调用kvmmake()
- kvminithart: kvminit之后，开启分页
- procinit: 初始化进程槽，将所有p->state初始化为UNUSED
- proc_mapstacks: 分配内核栈
---
实现中的技术细节:
- 概览:
    - 1.修改proc加入k_pagetable(kpgtbl copy)
    - 2.修改allocproc, freeproc 加入创建释放k_pagetable的代码
    - 3.将为所有进程分配内核栈的mapstack逻辑改成每个进程自己调用分配
    - 4.减少kvmmake的工作，使它只建立必需的映射(global)。
    - 5.增加kvmunmap(inspired by freewalk) : 释放k_pagetable整张页表(包括映射位，中间页表)，但是不释放叶子页(data page)
    - 6.scheduler: 在swtch之前更换成k_pagetable，因为:1.scheduler可以在k_pagetable上运行 2.swtch立刻离开scheduler 3.再次进入scheduler必然经过prepare_return(), 它会重新将global内核页表写入satp
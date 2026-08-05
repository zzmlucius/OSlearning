## 整个虚拟地址空间和整个物理地址空间之间的映射

![kernel virtual address mapping to the physical address](vapa.png)

- **1.右边Physical memory 和 Unused合为DRAM**

- **2.KERNBASE之下及从KERNBASE到PHYSTOP都采用直接映射，即物理地址与虚拟地址相同**

- 3.Kenel data中有内核栈数据，PHTSTOP之上的Kstack也有一样的内核栈的数据，这里他们映射到了同一个物理地址。
### sys_sbrk 只负责改变 p->sz, 核心代码都在 kerneltrap 和 usertrap

- 核心过程:
    - 访问非法地址触发page fault:
        - pc->stvec
    - usertrap/kerneltrap:
        - 判断
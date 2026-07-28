//The stucture of xv6 proc and the design of context switch
```c
struct context {
        int eip; // 程序计数器
        int esp; // 栈指针

        int ebx; // 通用寄存器
        int ecx;
        int edx;
        int esi;
        int edi;

        int ebp; // 栈基址
}

enum proc_state { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

// the information xv6 tracks about each process
// including its register context and state

struct proc {
        char *mem;              // 这两行就是进程的内存地址
        uint sz;
        char *kstack;           // 一个进程不仅有用户态还有内核态，用户态维护>栈指针，内核态也维护一个kernel stack

        enum proc_state state;  // Process state
        int pid;                // Process id
        sturce proc *parent;    // Parent process
        void *chan;             // If non-zero, sleeping on chan
        int killed;
        struct file *ofile[NOFILE];// Open file
        struct inode *cwd;      // Current directory
        struct context context  // Switch here to run process
        struct trapframe *tf    // Trap frame for the current interrupt

};
```
// trapframe：用户态 ↔ 内核态的边界(保护用户现场)
// context：内核调度时进程之间切换(保存内核现场)

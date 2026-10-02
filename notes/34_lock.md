### LOCK (OS level)

- lock implement :
```c
// Mutual exclusion lock.
struct spinlock {
  uint locked; // Is the lock held?

  // For debugging:
  char *name;      // Name of lock.
  struct cpu *cpu; // The cpu holding the lock.
};

// __atomic_exchange_n 是由C库实现的，保证了操作原子性
void
acquire(struct spinlock *lk)
{
  push_off(); // disable interrupts to avoid deadlock.
  if (holding(lk))
    panic("acquire");

  while (__atomic_exchange_n(&lk->locked, 1, __ATOMIC_ACQUIRE) != 0)
    ;

  // Record info about lock acquisition for holding() and debugging.
  lk->cpu = mycpu();
}
```

- OS层面的lock一般为CPU lock, 即避免两个CPU上的进程同时修改一个共享数据结构

- API : acquire() and release()

- When to lock ?
    - 2 proc access a shared data structure
    - but it's too strict for lock-free program
    - too loose for printf("")

- Could locking be auto ?(bound with data structure itself) (important)
    - lock should be connect with operation, not data structure!

- Lock Perspective (important)
    - avoid lost updates
    - make multi-step op atomic
    - maintain invariant

- Lock vs. modularity & performance

- technique: 防止编译器优化修改并发代码顺序
    - __sync_synchronize(): 任何在这行代码之前的代码都不能被移动到这行代码之后

---

### 锁的归属问题
- 当一个进程持有自旋锁时，CPU不能切换。所以"锁归CPU"和"锁归进程"在效果上时一致的
- 锁处于一种共享的状态，它不保存在进程上下文中
- 为什么不用普通锁代替p->lock：这个锁的用途是使不同CPU上的调度器访问进程的状态串行。如果使用普通的所就需要NPROC把，这样会变复杂
- p->lock是“管理进程状态”和“调度器切换进程”的。如果没有acquire(&p->lock), 那么进程状态将会被多个进程或调度器修改
- 当你使用swtch时不能持有其他的锁除了p->lock

### hartid
- 在CPU启动之前，hartid就已经确定了。
- CPU启动时读取hartid
- 在xv6中规定hartid存储在当前CPU的tp寄存器中
- mycpu()读取tp寄存器
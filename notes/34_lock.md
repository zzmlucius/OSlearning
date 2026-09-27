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
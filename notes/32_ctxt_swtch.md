#### Context Switch
- mycpu() -> context保存该CPU核的调度器执行现场
- 同一个CPU总是在执行调度器或某个进程

定时器引起的进程切换：
- 定时器到期（硬件）
 → CPU 进入中断入口:
    - sepc   ← 被打断的用户 PC
    - scause ← 定时器中断原因
    - sstatus.SPP ← 原模式 U
    - sstatus.SPIE ← 原来的中断状态
    - 关闭当前层中断
    - PC ← stvec
 → uservec / kernelvec
 → usertrap() / kerneltrap()
 → devintr()
 → clockintr()
 → 返回 trap 处理函数，调用 yield()
 → sched()
 → swtch(当前进程上下文, 调度器上下文)
 → scheduler()
 → swtch(调度器上下文, 下一个进程上下文)

swtch.S :
先将P的ra存入p->context, 然后从c->context载入调度器的ra和sp,然后ret就会根据之前“从调度器切换回进程”时的ra回到scheduler
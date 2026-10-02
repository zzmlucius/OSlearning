### sleep() and wakeup()

#### sleep() API
- for sleep(void *chan, struct spinlock *lk):
    - before : hold lk
    - ing    : release
    - after  : rehold !

#### lost sleep
- 唤醒发生在真正的睡眠之前
- 此时，call sleep()的进程还没有执行p->status = SLEEPING，另外一个进程获得了该进程的锁然后call wakeup(), 并且此时没有发现SLEEPING进程
- 前者的sleep()继续执行到state = SLEEPING, 之后没有进程再来唤醒它
- 此时就会lost wakeup

#### 过程
- 在sleep()之前获得lk
- 使while(chechking shared var) sleep();循环安全检查shared var
- 在sleep中获得p->lock,释放lk使得proc安全sched()
- lk防止shared var被修改
- p->lock 防止提前 wakeup()导致lost sleep
- attention:
    - p->lock 不是睡眠期间一直持有！只持有到完成上下文切换，进入scheduler之后会释放p->lock
    - sleep(void *chan, spinlock *lock)会在被唤醒时重新获得lock

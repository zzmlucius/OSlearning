低级的协议：上下文切换，停止运行一个program,然后切换到另外一个，时分共享
高级的机制：调度策略scheduling policy

将protocol和policy分离：一个是如何执行上下文切换，另一个是选择哪个程序运行。

进程	API:1.create 2.destroy 3.wait 4.miscellaneous control 5.status

进程的机器状态：内存，寄存器(状态机)

1.操作系统运行程序必须做的第一件事是将代码和所有静态数据（例如初始化变量）加
载（load）到内存中，加载到进程的地址空间中。2.还会参数化初始栈。3.还有I/O的初始化：比如UNIX给每个进程初始化三个打开文件描述符：file descriptor。

进程地址空间（process address space）是操作系统为每个进程提供的一套独立的虚拟内存地址范围，进程认为自己独占这片内存

最后OS将控制权移交给新创建的线程，从而程序开始执行。

进程状态：运行，就绪，阻塞（scheduling policy）

进程间切换都发生在内核态。


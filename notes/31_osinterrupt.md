### The driver code and the hardware interrupts(and handler)
围绕shell如何向屏幕输出'$', 和当你输入ls并回车时字符如何传输给CPU, 以及当CPU运行ls程序时，怎么向屏幕输出。
overview : 1:async 2.concurrency 3.program device(!)
overview2: the driver code structure
overview3: software abstraction console
- 1. device gen intr to CPU (bottom half)
- 2. OS gen intr to device (top half)

#### How the UART work (hardware)
**UART负责收发字符**:
- 字符到达 UART
- UART 硬件接收并保存字符
- UART 向 PLIC 提出中断请求
- PLIC 向 CPU 提出外部中断请求
- CPU 暂停原来的执行流，进入中断处理
- uartintr()
- CPU 从 UART 寄存器读取字符 uartgetc()
- console将收到的字符放入缓冲区
- 收到回车后，console唤醒正在等待输入的shell

注意这里字符接收之后才产生中断, 输入字符“瞬间”是没有中断的
#### two kind of intrs and true concurrency
- 1. 硬件产生的intr是完全独立于进程的
- 2. 软件产生的intr比如主动调用uartintr()是有进程上下文的

#### between the uart and shell : console
Console 还会解释特殊字符：
- Backspace：删除一个字符
- Ctrl-U：删除整行
- Ctrl-D：表示 EOF
- Enter：表示一行输入完成
**Console 和 UART的区别: UART不理解字符只是传输字符，Console理解并管理字符及缓冲区, 唤醒Shell**

#### 轮询 or sleep : 当CPU监听对应硬件时采用的策略
- 如果目标硬件频繁向CPU发送请求，轮询会更省时
- 如果目标硬件很慢很空闲，那么就采用sleep
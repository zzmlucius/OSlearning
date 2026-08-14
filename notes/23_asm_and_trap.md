## RISC-V常见指令

- li   : load immediate 将立即数加载到指定寄存器
- csrr : 读csr寄存器到指定寄存器
- csrw : 写指定寄存器到csr寄存器
- sd   : store doubleword, 将寄存器中64位数写入内存, 比如sd t0, 8(sp), 表示把 t0 中的 64 位数据存到地址 sp + 8
- sfence.vma : Supervisor Fence Virtual Memory Address, 让此前对页表的修改生效，并使处理器不再使用相关的旧地址转换缓存（TLB）记录。
- jalr : jump and link register, jalr rd, offset(rs1) : rd = pc + 4 pc = (rs1 + offset) & ~1
trap处理中jalr t0, 即pc = t0

## ecall & sret
- sstatus(控制妆台寄存器): 三个比特位
    - SIE  supervisor interrupt enable
    - SPIE supervisor previous interrupt enable
    - SPP  supervisor previous priviliege 记录进入trap前处于什么mode, 用于sret返回

- ecall :
    - usermod -> kernel mode
    - 将pc中的值存到sepc
    - pc存储stvec中的值
    - SPP = 当前特权级
    - SIE = 0关闭中断 (当前为user, 所以为0)

- sret : supervisor return :
    - pc = sepc
    - SIE = SPIE
    - SPIE = 1 
    - SPP = 0

## trap处理的大概流程


## Driver code structure and API design
- 1.区分硬件和驱动的职责
- 2.以intel E1000 network-card为例:
    - 实际上的driver code很精简:
        - 只包含了init, transmit, recv, intr
        - 这些接口的上下文很清晰
        - 对于e1000_transmit，驱动只需将数据的状态写入硬件协议规定的数据结构
        - 对于e1000_recv, 驱动上层接口为intr, 下层接口为net_rx, 
        驱动只需从硬件协议规定的数据结构读取数据，然后将数据传给net_rx(他会完成数据之后的传输)
    - 按照划分:driver分为top half , bottom half
        - top    half : 起始调用者为OS
        - bottom half : 起始调用者为硬件
    - 良好实现的API可使coder无需知道API的另一端的实现，只需知道当前的状态，以及接下来需要的状态，就可以继续编写代码
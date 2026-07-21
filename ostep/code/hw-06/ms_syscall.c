#include <stdio.h>
#include <stdlib.h> 
#include <x86intrin.h>
#include <unistd.h>

int main(int argc, int *argv[])
{
    __uint64_t start = __rdtsc();  //read time stamp counter,是一条汇编指令,表示自CPU启动以来的计数值 
    for(int i = 1;i <= 1000000;i++) {
        getpid();
    }
    __uint64_t end = __rdtsc();
    
    printf("%llu\n", end - start);  //返回值的单位是CPU周期
} //平均是320705418，共1000000syscall, 平均下来一个系统调用是320个CPU cycle
// 而我的电脑大概平均是2GHz,也就是一个cycle 0.5ns,160ns

//lmbench测试context switch时间开销
#define _GNU_SOURCE
#define N 1000000
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <x86intrin.h>
#include <sys/wait.h>
#include <sched.h>

int main(int argc, int *argv)  //利用原理，pipe为空，写端开着，读端将会度塞
{

    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    sched_setaffinity(0, sizeof(set), &set);

    int fd1[2];
    int fd2[2];
    int a = pipe(fd1);
    int b = pipe(fd2);
    if(a || b) {
        fprintf(stderr, "create pipe failed.");
        exit(1);
    }

    char c = 'a';

    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed.");
        exit(1);
    }

    if(rc == 0) { //创建成功
        close(fd2[0]);
        close(fd1[1]);
        for(int i = 1;i <= N;i++) {
            write(fd2[1], &c, 1);
            read(fd1[0], &c, 1);
        }
        exit(0);
    }


    close(fd2[1]);
    close(fd1[0]);
    __uint64_t start = __rdtsc();
    for(int i = 1;i <= N;i++) {
        write(fd1[1], &c, 1);
        read(fd2[0], &c, 1);
    }
    __uint64_t end = __rdtsc();
    wait(NULL);

    printf("cycles/context switch = %.2f\n",
       (double)(end - start) / (2 * N)); 
       //每轮都是两次context switch,四次syscall
    
    return 0;
} //这里算出来的是一次context switch两次syscall的值
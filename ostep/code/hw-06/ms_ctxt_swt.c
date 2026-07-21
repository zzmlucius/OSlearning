//lmbench测试context switch时间开销
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <x86intrin.h>
#include <sys/wait.h>
#include <sched.h>

#define WARMUP 10000
#define N 1000000

int main(void)
{
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);

    if (sched_setaffinity(0, sizeof(set), &set) == -1) {
        perror("sched_setaffinity");
        exit(1);
    }

    int fd1[2];
    int fd2[2];

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("pipe");
        exit(1);
    }

    char c = 'a';

    int rc = fork();
    if (rc < 0) {
        perror("fork");
        exit(1);
    }

    if (rc == 0) {
        close(fd2[0]);
        close(fd1[1]);

        /* warm-up */
        for (int i = 0; i < WARMUP; i++) {
            write(fd2[1], &c, 1);
            read(fd1[0], &c, 1);
        }

        /* benchmark */
        for (int i = 0; i < N; i++) {
            write(fd2[1], &c, 1);
            read(fd1[0], &c, 1);
        }

        close(fd1[0]);
        close(fd2[1]);
        exit(0);
    }

    close(fd2[1]);
    close(fd1[0]);

    /* warm-up */
    for (int i = 0; i < WARMUP; i++) {
        write(fd1[1], &c, 1);
        read(fd2[0], &c, 1);
    }

    _mm_lfence();
    __uint64_t start = __rdtsc();

    for (int i = 0; i < N; i++) {
        write(fd1[1], &c, 1);
        read(fd2[0], &c, 1);
    }

    _mm_lfence();
    __uint64_t end = __rdtsc();

    wait(NULL);

    close(fd1[1]);
    close(fd2[0]);

    printf("Total cycles: %llu\n",
           (unsigned long long)(end - start));

    printf("Cycles / ping-pong: %.2f\n",
           (double)(end - start) / N);

    printf("Cycles / context switch: %.2f\n",
           (double)(end - start) / (2.0 * N));

    return 0;
}
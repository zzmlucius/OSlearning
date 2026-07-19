#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main(int argc, int *argv[])
{
    int status;
    int pid = fork();
    if(pid < 0) {
        fprintf(stderr, "fork failed");
        exit(1);
    }
    else if(pid == 0) {
        close(STDOUT_FILENO);
        printf("Hello\n");
    }
    else {
        wait(&status);
        printf("status = %d\n", status);
    }
}
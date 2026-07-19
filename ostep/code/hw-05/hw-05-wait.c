#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc, int *argv[])
{
    int pid = fork();
    int status;
    if(pid < 0) {
		fprintf(stderr, "fork failed");
	}
	else if(pid == 0) {
        wait(NULL);
		printf("I'm child");
	}
	else {
        wait(&status);
		printf("I'm parent, %d\n", status);
	}
}

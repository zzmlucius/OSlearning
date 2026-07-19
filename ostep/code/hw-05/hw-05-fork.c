#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, int *argv[])
{
	int pid = fork();
	int x = 0;
	if(pid < 0) {
		fprintf(stderr, "fork failed");
	}
	else if(pid == 0) {
		printf("I'm child, pid = %d\n", int(getpid);
	}
	else {
		printf("I'm parent, pid = %d\n",int(getpid());
	}
}

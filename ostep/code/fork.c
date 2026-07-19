#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed");
	}
	else if(rc == 0) {
		printf("Hello, I'm child, pid = %d\n", (int) getpid);
	}
	else {
		printf("Hello, I'm parent, pid = %d\n", (int) getpid());
	}
	return 0;
}

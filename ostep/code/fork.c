#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	printf("Hello World (pid:%d)\n", (int) getpid());
	int rc = fork();
	if (rc < 0) {

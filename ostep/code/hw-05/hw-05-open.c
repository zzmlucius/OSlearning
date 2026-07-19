#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     //write read close fork
#include <fcntl.h>      //open
#include <sys/stat.h>   //文件状态宏
#include <sys/wait.h>   //wait

int main(int argc, int *argv[]) {
    //close(STDOUT_FILENO); //#define STDOUT_FILENO 1
    int fd = open("./output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    int rc = fork();
    char str1[] = "Hellochi";
    char str2[] = "Hellopar";  
    if(rc < 0) {
        fprintf(stderr, "fork failed.");
        exit(1);
    }
    else if(rc == 0) {
        write(fd, str1, 8);
    }
    else {
        write(fd, str2, 8);
    }
    return 0;
}

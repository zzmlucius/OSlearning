#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> //   fork,read,write,close
#include<sys/wait.h>

int main(int argc, int *argv[])
{
    int fd[2];          //用来保存管道的两个文件描述符
    pipe(fd);           //创建管道fd[1]管道写端文件描述符，fd[0]管道读端文件描述符

    if(fork() == 0) {
        dup2(fd[1], STDOUT_FILENO); //将STDOUT_FILENO重新指向fd[1].
        close(fd[0]);   //这里管道读端没用
        close(fd[1]);   //注意这里，STDOUT_FILENO和fd[1]都指向管道写端
        execlp("ls", "ls", NULL);
    }

    if(fork() == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);
        execlp("wc", "wc", "-l", NULL);
        
    }
    close(fd[0]);
    close(fd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
} //相当于ls | wc -l
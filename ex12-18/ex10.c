#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t cpid;
    char buf;
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (pipe(pipefd) == -1)
    { 
        /* 创建匿名管道 */
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    cpid = fork(); /* 创建子进程 */
    if (cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0)
    {                     /* 子进程读管道读端 */
        close(pipefd[1]); /* 关闭不需要的写端 */
        while (read(pipefd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);
    }
    else
    {                     /* 父进程写 argv[1]到管道 */
        close(pipefd[0]); /* 关闭不需要的读端 */
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]); /* 关闭文件发送 EOF，子进程停止读*/
        wait(NULL);       /* 等待子进程退出 */
        exit(EXIT_SUCCESS);
    }
}
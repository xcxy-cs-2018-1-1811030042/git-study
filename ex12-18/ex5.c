#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
char *env_init[] = {"USER=peng", "HOME=/root/git-study/ex12-18/", NULL}; /* 为子进程定义环境变量 */
int main(int argc, char *argv[])
{
    pid_t pid;
    if ((pid = fork()) < 0)
    { /* 创建进程失败判断 */
        perror("fork error");
    }
    else if (pid == 0)
    {                                                                                   /* fork 对子进程返回 0 */
        execle("/root/git-study/ex12-18//sample3", "sample3", "hello", "world", (char *)0, env_init); /*子进程装载新程序*/
        perror("execle error");                                                         /* execle 失败时才执行 */
        exit(-1);
    }
    else
    {
        exit(0); /* 父进程退出 */
    }
    return -1;
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    pid_t pid;
    pid = fork(); /* 创建进程 */
    if (pid == 0)
    {                                                                                   /* 对子进程返回 0 */
        printf("Here is child, my pid = %d, parent's pid = %d\n", getpid(), getppid()); /* 打印父子进程 PID */
        
        exit(0);
    }
    else if (pid > 0)
    { /*对父进程返回子进程 PID */
        printf("Here is parent, my pid = %d, child's pid = %d\n", getpid(), pid);
         printf("pid:%d\n",pid);
    }
    else
    { /* fork 出错 */
        perror("fork error\n");
    }
    return 0;
}
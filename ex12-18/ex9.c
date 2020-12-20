#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
void print_exit_status(int status)
{ /* 打印子进程退出状态信息 */
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status)) /* 是否未信号引起退出 */
        printf("abnormal termination, signal number = %d\n", WTERMSIG(status));
    else
        printf("other status\n");
}
int main(int argc, char *argv[])
{
    pid_t pid;
    int status;
    if ((pid = fork()) < 0)
    {
        perror("fork error");
        exit(-1);
    }
    else if (pid == 0)
    { /* 子进程 */
        while (1)
        {
            printf("chlid sleeping\n");
            sleep(1);
        }
        exit(0);
    }
    else
    {
        sleep(2);
        printf("parent send SIGINT to child\n");
        kill(pid, SIGINT); /* 向子进程发送 SIGINIT 信号 */
        if (wait(&status) != pid)
        { /* 获取子进程的退出状态 */
            perror("wait error");
            exit(-1);
        }
        print_exit_status(status);
    }
    return 0;
}
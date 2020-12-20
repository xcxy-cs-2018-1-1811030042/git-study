#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void print_exit_status(int status)
{                          /* 自定义打印子进程退出状态函数 */
    if (WIFEXITED(status)) /* 正常退出，打印退出返回值 */
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status)) /* 因信号异常退出，打印引起退出的信号 */
        printf("abnormal termination, signal number = %d\n", WTERMSIG(status));
    else
        printf("other status\n"); /* 其它错误 */
}
int main(int argc, char *argv[])
{
    pid_t pid;
    int status;
    if ((pid = fork()) < 0)
    { /* 创建子进程 */
        perror("fork error");
        exit(-1);
    }
    else if (pid == 0)
    {
        exit(7); /* 子进程调用 exit 函数，参数为 7 */
    }
    if (wait(&status) != pid)
    { /* 父进程等待子进程退出，并获取退出状态*/
        perror("fork error");
        exit(-1);
    }
    print_exit_status(status); /* 打印退出状态信息 */
    if ((pid = fork()) < 0)
    { /* 创建第二个子进程 */
        perror("fork error");
        exit(-1);
    }
    else if (pid == 0)
    {
        abort(); /* 子进程调用 abort()函数异常退出 */
    }
    if (wait(&status) != pid)
    { /* 父进程等待子进程退出，并获取退出状态*/
        perror("fork error");
        exit(-1);
    }
    print_exit_status(status); /* 打印第二个退出状态信息 */
    return 0;
}
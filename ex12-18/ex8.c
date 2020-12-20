#include <unistd.h>
#include <stdio.h>
#include <signal.h>
void ouch(int sig)
{ /* 信号处理函数 */
    printf("\nOuch! - I got signal %d\n", sig);
}
int main(int argc, char *argv[])
{
    struct sigaction act;
    act.sa_handler = ouch;         /* 设置信号处理函数 */
    sigemptyset(&act.sa_mask);     /* 清空屏蔽信号集 */
    act.sa_flags = SA_RESETHAND;   /* 设置信号处理之后恢复默认的处理方式 */
    sigaction(SIGINT, &act, NULL); /* 设置 SIGINT 信号的处理方法 */
    while (1)
    { /* 进入循环等待信号发生 */
        printf("sleeping\n");
        sleep(1);
    }
    return 0;
}
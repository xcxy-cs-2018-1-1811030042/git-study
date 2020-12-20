#include <unistd.h>
#include <stdio.h>
pid_t getpid(void);
int main()
{
    printf("current process pid = %d\n", getpid());
}
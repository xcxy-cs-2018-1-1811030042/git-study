#include <stdio.h>
extern char **environ;
int main(int argc, char *argv[])
{
    int i = 0;
    while (environ[i])
        puts(environ[i++]);
    return 0;
}
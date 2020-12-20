#include <stdio.h>
int main(int argc, char *argv[], char *env[])
{
    int i = 0;
    while (env[i])
        puts(env[i++]);
    return 0;
}
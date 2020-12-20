#include <stdlib.h>
#include<stdio.h>
char *getenv(const char *name);

int main()
{
    char *env;
    env = getenv("http_proxy");
    puts(env);
}
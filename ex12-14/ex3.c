#include <sys/types.h> /* 定义数据类型，如 ssize_t，off_t 等 */
#include <fcntl.h>     /* 定义 open，creat 等函数原型，创建文件权限的符号常量 S_IRUSR 等 */
#include <unistd.h>    /* 定义 read，write，close，lseek 等函数原型 */
#include <errno.h>     /* 与全局变量 errno 相关的定义 */
int main(int argc, char* argv[])
{
    char sz_filename[] = "hello.txt";
    int fd;
    fd = open(sz_filename, O_CREAT | O_WRONLY | O_TRUNC, 0x664);
    // ....
}
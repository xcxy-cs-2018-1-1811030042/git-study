#include <sys/types.h> /* 定义数据类型，如 ssize_t，off_t 等 */
#include <fcntl.h>     /* 定义 open，creat 等函数原型，创建文件权限的符号常量 S_IRUSR 等 */
#include <unistd.h>    /* 定义 read，write，close，lseek 等函数原型 */
#include <errno.h>     /* 与全局变量 errno 相关的定义 */
#include<stdio.h>
int main(int argc, char *argv[])
{
    char sz_str[] = "Hello, welcome to linux world!!";
    char sz_filename[] = "hello.txt";
    int fd = -1;
    int res = 0;
    char buf[128] = {0};

    fd = open(sz_filename, O_WRONLY | O_CREAT,                  /* 以只写、创建打开文件 */
              S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH); /* 权限模式 mode=0x664 */
    if (fd < 0)
    {
        printf("open file \"%s\" failed, errno=%d.\n",
               sz_filename, errno);
        return -1;
    }

    res = write(fd, sz_str, sizeof(sz_str)); /* 写文件 */
    printf("write %d bytes to \"%s\".\n", res, sz_filename);
    fsync(fd); /* 同步文件 */
    close(fd); /* 关闭文件 */

    fd = open(sz_filename, O_RDONLY); /* 从只读方式打开文件 */
    if (fd < 0)
    {
        printf("open file \"%s\" failed, errno=%d.\n",
               sz_filename, errno);
        return -1;
    }

    res = read(fd, buf, sizeof(buf)); /* 读文件 */
    buf[res] = '\0';
    printf("read %d bytes from file \"%s\", data=\"%s\"\n",
           res, sz_filename, buf);
    close(fd);

    return 0;
}
// file_lseek.c

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
int main(int argc, char *argv[])
{
    int fd = -1;
    int res, cur, new_cur, offset = 0;
    char sz_filename[] = "hello.txt";
    char buf[128] = {0};

    fd = open(sz_filename, O_RDONLY); /* 以只读方式打开文件 */
    if (fd < 0)
    {
        printf("open file failed, errno=%d.\n", errno);
        return -1;
    }

    res = read(fd, buf, 6); /* 文件刚打开时，读写位置在开头，从开头起读 6 字节 */
    buf[res] = '\0';
    printf("read %d bytes from file \"%s\","
           " offset=%d, data=\"%s\"\n",
           res, sz_filename, offset, buf);

    cur = lseek(fd, 0, SEEK_CUR);          /* 获取当前读写位置 */
    offset = 18 - cur;                     /* 要移动到偏移 18 字节的位置读数据 */
    new_cur = lseek(fd, offset, SEEK_CUR); /* 从当前位置 6，移到 18 */
    if (new_cur == -1)                     /* 检查操作是否成功 */
        printf("lseek failed, errno=%d.\n", errno);
    else
        printf("SEEK_CUR: current=%d, offset=%d, new_cur=%d.\n",
               cur, offset, new_cur);
    res = read(fd, buf, sizeof(buf)); /* 请求字节数大于文件长度，将读到文件结尾 */
    buf[res] = '\0';
    printf("read %d bytes from file \"%s\","
           " offset=%d, data=\"%s\"\n",
           res, sz_filename, new_cur, buf);

    cur = lseek(fd, 0, SEEK_END);          /* 这个方法可以得到文件长度 */
    offset = -7;                           /* 从结尾往开头，所以是负数 */
    new_cur = lseek(fd, offset, SEEK_END); /* 移动到反偏移 7 字节处 */
    if (new_cur == -1)
        printf("lseek failed, errno=%d.\n", errno);
    else
        printf("SEEK_END: current=%d, offset=%d, new_cur=%d.\n",
               cur, offset, new_cur);
    res = read(fd, buf, sizeof(buf));
    buf[res] = '\0';
    printf("read %d bytes from file \"%s\","
           " offset=%d, data=\"%s\"\n",
           res, sz_filename, new_cur, buf);
    close(fd); /* 关闭文件 */
    return 0;
}
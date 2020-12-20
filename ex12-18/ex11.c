#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#define BUFSIZE 1024 /* 一次最大写 1024 个字节 */
int main(int argc, char *argv[])
{
    const char *fifoname = "/tmp/fifo"; /* 命名管道文件名 */
    int pipefd, datafd;
    int bytes, ret;
    char buffer[BUFSIZE];
    if (argc != 2)
    { /* 带文件名参数 */
        fprintf(stderr, "Usage: %s < filename >\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (access(fifoname, F_OK) < 0)
    {                                 /* 判断文件是否已存在 */
        ret = mkfifo(fifoname, 0777); /* 创建管道文件 */
        if (ret < 0)
        {
            perror("mkfifo error");
            exit(EXIT_FAILURE);
        }
    }
    pipefd = open(fifoname, O_WRONLY); /* 打开管道文件 */
    datafd = open(argv[1], O_RDONLY);  /* 打开数据文件 */
    if ((pipefd > 0) && (datafd > 0))
    { /* 将数据文件读出并写到管道文件 */
        bytes = read(datafd, buffer, BUFSIZE);
        while (bytes > 0)
        {
            ret = write(pipefd, buffer, bytes);
            if (ret < 0)
            {
                perror("write error");
                exit(EXIT_FAILURE);
            }
            bytes = read(datafd, buffer, BUFSIZE);
        }
        close(pipefd);
        close(datafd);
    }
    else
    {
        exit(EXIT_FAILURE);
    }
    return 0;
}
// file_ioctl.c

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
/* 
 * 通过交替发送不同的 cmd 到蜂鸣器设备，并控制适当
 * 的延时时间，会听到有规律的鸣叫声，嘀－嘀嘀嘀
 */
int main(int argc, char *argv[])
{
    int fd = -1;                        /* 文件描述符 */
    char sz_dev[] = "/dev/imx283_beep"; /* 蜂鸣器设备文件名 */
    int cmd = 0;                        /* 蜂鸣器操作命令码，0-鸣叫，1-静音 */

    fd = open(sz_dev, O_RDWR); /* 以可读写方式打开，忽略最后一个参数 mode */
    if (fd == -1)              /* 打开文件失败时的错误处理 */
    {
        printf("open device file \"%s\" failed, err=%d\n", sz_dev, errno);
        return errno;
    }

    cmd = 0; /* 发鸣叫命令 */
    ioctl(fd, cmd);
    usleep(400 * 1000); /* 延时 400 毫秒 */

    for (cmd = 1; cmd < 8; cmd++)
    { /* 循环发送 7 次命令 */
        ioctl(fd, 0x01 & cmd);
        usleep(200 * 1000); /* 延时 200 毫秒 */
    }

    close(fd); /* 关闭设备 */
    return 0;
}
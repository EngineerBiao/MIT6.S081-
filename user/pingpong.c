#include "kernel/types.h" // 声明了基本类型
#include "user/user.h" // 包含系统调用和常用函数
int main(int argc, const char *argv[])
{
	char p = 'p'; // 要发送的字节，既能作为写缓冲区也能作为读缓冲区
    int fd_c2p[2]; // 儿子写给父亲
    int fd_p2c[2]; // 父亲写给儿子
    pipe(fd_c2p); // 创建管道
    pipe(fd_p2c);
    int pid;
    if ((pid = fork()) < 0)
    {
        fprintf(2, "fork error\n");
        close(fd_c2p[0]);
        close(fd_c2p[1]);
        close(fd_p2c[0]);
        close(fd_p2c[1]);
        exit(1);
    }
    if (pid == 0) // 子进程
    {
        close(fd_c2p[0]);
        close(fd_p2c[1]);
        if (read(fd_p2c[0], &p, sizeof(p)) != sizeof(p))
        {
            fprintf(2, "child read error\n");
            exit(1);
        }
        else
            fprintf(1, "%d: received ping\n", getpid());
        if (write(fd_c2p[1], &p, sizeof(p)) != sizeof(p))// 写字节给父进程
        {
            fprintf(2, "child write error\n");
            exit(1);
        }
        close(fd_c2p[1]);
        close(fd_p2c[0]);
    }
    else // 父进程
    {
        close(fd_c2p[1]);
        close(fd_p2c[0]);
        if (write(fd_p2c[1], &p, sizeof(p)) != sizeof(p))
        {
            fprintf(2, "parent write error\n");
            exit(1);
        }
        if (read(fd_c2p[0], &p, sizeof(p)) != sizeof(p))
        {
            fprintf(2, "parent read error\n");
            exit(1);
        }
        else
            fprintf(1, "%d: received pong\n", getpid());
        close(fd_c2p[0]);
        close(fd_p2c[1]);
    }
    exit(0);
}

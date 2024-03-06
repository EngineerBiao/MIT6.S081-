#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, const char *filename)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "cannot open %s\n", path);
        return;
    }
    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "cannot stat %s\n", path);
        close(fd);
        return;
    }
    if (st.type != T_DIR) // find的第一个参数必须是目录
    {
        fprintf(2, "usage: find <DIRECTORY> <filename>\n");
        return;
    }
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) // 防止路径名过长溢出
    {
        printf("ls: path too long\n");
        return;
    }
    // 构建完整文件路径，用于之后的完整文件路径输出和stat函数
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    // 当fd是一个目录时，他的内容就是一个个de大小的结构体，当read读取的内容不为结构体时说明读完目录项
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
        if (de.inum == 0) // inum为0表示该目录未使用
            continue;
        // 前面已经构建了文件路径，这里就是把目录项中的文件/目录名添加上，在后面对该文件进行操作
        memmove(p, de.name, DIRSIZ); // 把文件/目录名赋值给p，p是一个指针，所以是修改了buf的内容
        p[DIRSIZ] = 0;               // 给字符串末尾添加结束符
        if (stat(buf, &st) < 0)
        {
            printf("ls: cannot stat %s\n", buf);
            continue;
        }
        // 如果是目录就递归调用find（即对子目录寻找文件）（不在“.”和“..”目录中递归）
        if (st.type == T_DIR && strcmp(p, ".") != 0 && strcmp(p, "..") != 0)
            find(buf, filename);
        else if (strcmp(filename, p) == 0) // 如果是文件且名字与寻找的相同，则输出完整的文件路径
            printf("%s\n", buf);
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(2, "usage: find <directory> <filename>\n");
        exit(1);
    }
    find(argv[1], argv[2]);
    exit(0);
}

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

// 函数作用：找到最后一个斜杠后面的文件名病进行格式化（就是在路径名后面添加足够的空格，在输出的时候更整齐）
// 为什么要找最后一个斜杠的文件名：例如 ls /home/biao，只会直接输出biao中的文件名而不会包含/home/biao
char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash. 注：找到最后一个斜杠后面的第一个字符的位置
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name. 注：如果p后面的文件名达到预定大小就直接返回，没达到就填充然后再返回
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void
ls(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE: // 如果ls的参数是文件，则直接打印该文件的文件名和属性
    printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR: // 如果参数是目录，打印该目录下的所有文件/目录的名字和属性
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    // 在当前路径后面加上'/'，后面会通过memove来添加最后的文件名。下面3行的作用是构建完整文件名，用于后面的stat函数
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    // 当fd是一个目录时，他的内容就是一个个de大小的结构体，当read读取的内容不为结构体时说明读完目录项
    while(read(fd, &de, sizeof(de)) == sizeof(de)){ 
      if(de.inum == 0) // inum为0表示该目录未使用
        continue;
      memmove(p, de.name, DIRSIZ); // 把文件/目录名赋值给p，p是一个指针，所以是修改了buf的内容
      p[DIRSIZ] = 0; // 给字符串末尾添加结束符
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    ls(".");
    exit(0);
  }
  for(i=1; i<argc; i++)
    ls(argv[i]);
  exit(0);
}

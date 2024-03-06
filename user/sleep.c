#include "kernel/types.h" // 声明了基本类型
#include "user/user.h" // 包含系统调用和常用函数

int main(int argc, const char *argv[])
{
  if (argc != 2) //参数错误
  {
    fprintf(2, "usage: sleep <time>\n"); // 写入标准错误
    exit(1);
  }
  sleep(atoi(argv[1]));
  exit(0);
}

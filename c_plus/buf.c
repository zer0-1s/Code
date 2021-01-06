#include "stdio.h"
#include "unistd.h"

void init()
{   //标准输入流或标准输出流无缓冲
    setbuf(stdin,0);
    setbuf(stdout,0);
}
int main()
{   init();//无缓冲输入,输出,可以更改Linux的缓冲输入,输出.
    char buf[0x10];
    printf("Please input in buffer:\n");//在Linux下默认会缓存字符，这也就是为什么有的pwn题会后输出printf
    read(0,buf,0x100);
    puts(buf);
    return 0;
}
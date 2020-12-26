#include"stdio.h" 
int main()
{  
    char ch;
    while((ch=getchar())!=EOF)
        putchar(ch);
    return 0;
}
/*
ctf@ubuntu:~/Desktop$ nano redirect.c 
ctf@ubuntu:~/Desktop$ gcc -g redirect.c -o redirect
ctf@ubuntu:~/Desktop$ ./redirect < poem
Keep true to the dreams of your youth.
( Johann Schiller )
程序将I/O设备与文件放在同等地位上
#define getchar() getc(stdin)
*/
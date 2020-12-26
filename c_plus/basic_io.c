/*after ANSI C publish ,getchar & putchar make relationship with stdio.h*/
#include"stdio.h" 
int main()
{  
    /*事实上getchar与putchar是宏定义下的函数供预处理器使用.
        #define getchar() getc(stdin)
    */
    char ch;
    /*这样的用户可以不限长的输入，是文本处理器的核心.*/
    while((ch=getc(stdin))!='#')/*int getc(FILE *stream)*/
        //putchar(ch);
        putc(ch,stdout);

    return 0;
    /*output:
            123 hello 
            123 hello 
            123
            123
            #
    */
   
}
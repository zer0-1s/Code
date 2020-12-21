/*after ANSI C publish ,getchar & putchar make relationship with stdio.h*/
#include"stdio.h" 
int main()
{  
    /*事实上getchar与putchar是宏定义下的函数供预处理器使用.*/
    char ch;
    /*这样的用户可以不限长的输入，是文本处理器的核心.*/
    while((ch=getchar())!='#')
        putchar(ch);
    return 0;
    /*output:
            123 hello 
            123 hello 
            123
            123
            #
    */
   
}
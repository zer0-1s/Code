#include"stdio.h"
int main()
{   /*an simple example given by GCC-Inline-Assembly-HOWTO*/
    int a=10;
    int b;
    printf("%d\n",b);
    __asm__( "movl %1, %%eax;\n\t"
             "movl %%eax, %0;"
             :"=r"(b)        /* output %0*/
             :"r"(a)         /* input  %1*/
             :"%eax"         /* clobbered register */
            );       
    printf("%d\n",b);/*we can see b is modify,1 and 0 represent a and b */
    /*next is the same example*/
    int src = 1;
    int dst;   

    asm ("mov %1, %0\n\t"
        "add $1, %0"
        : "=r" (dst) 
        : "r" (src));

    printf("%d\n", dst);
    return 0;
}

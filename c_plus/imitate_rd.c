#include"stdio.h"
#include"stdlib.h"
#include"malloc.h"
#include"unistd.h"
#include "string.h"
#define MAX_DIR 100
/*
char * cd_dir(char *p)
{   
    char mem[MAX_DIR];
    char *temp;
   temp=mem;
    while(*p!='\0')
   {
        if(*p!='\\')
        {
            *temp=*p;
            p++;
            temp++;
        }
        else
        {
            *temp=*p;
          
            p++;
            temp++;
        }
    *temp='\0';
    return mem;
}
}
*/
int Conut_length(char *p)
{
    int len=0;
    while(*p!='\0')
     {
      len++;
      p++;
     }
     return len;
}
char* String_Add(char* p,char* q,int strlen)
{
    char * temp;
    temp=p;
    while(*p!='\0')
    p++;
    while(*q!='\0')
    {*p=*q;
     p++;
     q++;
    }
    *p=*q;
    return temp;
}
void  main()
{   char buf[100];
    char * temp="\\basic_io.c";
    char *filename;
    int len;
    char ch;
    memset(buf,0,sizeof(char)*100);
    char *pwd =getcwd(buf, sizeof(buf));
    printf("%s\n",pwd);
    len=Conut_length(pwd);
    filename=String_Add(pwd,temp,len);
    FILE *fp;
    //puts("please input the name of file you want to open:");
    fp=fopen(filename,"r");
    if(fp==NULL)
    printf("open the %s failed\n ",filename);
    while((ch=getc(fp))!=EOF)
        putchar(ch);
}
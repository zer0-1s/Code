#include"stdio.h"
#include"stdlib.h"
#include"malloc.h"
#include"unistd.h"
/*assume redirect is not usable*/
int main()
{
    char buf[1024];
    char *cwd =getcwd(buf, sizeof(buf));/*find the path is an error*/
    printf("%s",cwd);
    char ch;
    char filename[50];
    memset(filename,0,sizeof(char)*50);/*make sure filename is NULL*/
    FILE *fp;
    puts("please input the name of file you want to open:");
    scanf("%s",filename);
    fp=fopen(filename,"r");
    if(fp==NULL)
    printf("open the %s failed\n ",filename);
    while((ch=getc(fp))!=EOF)
        putchar(ch);
    return 0;
}
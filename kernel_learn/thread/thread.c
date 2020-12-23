#include"stdio.h"
#include"stdlib.h"
#include"pthread.h"
void * func(void *args)
{
    //printf("this is child threads");
    for(int i=0;i<50;i++)
    printf("%d\n",i);
    return 0;
}
int main()
{
    pthread_t th1,th2;
    pthread_create(&th1,NULL,func,NULL);
    pthread_create(&th2,NULL,func,NULL);
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);/*可以看到数字交错输出*/
    return 0;
}
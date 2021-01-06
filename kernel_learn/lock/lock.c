#include "stdio.h"
#include "stdlib.h"
#define N 6
#define M 8
//参考C++函数构造随机置换
int myrandom(int i){return rand()%i;}
void swap(int *p,int *q)
{
    int temp;
    temp=*p;
    *p=*q;
    *q=temp;
    return ;
}
void myrandom_shuffle(int* vector, int n,int (*p)(int i))
{
  int i;
  for (i=n-1; i>0; --i) {
    swap (&vector[i],&vector[p(i+1)]);
  }
    return ;
}

int main()
{
    int array[8]={1,2,3,4,5,6,7,8};
    int * p;
    int i,j=5;
    while(j>0)
    {
    p=array;
    myrandom_shuffle(p,8,myrandom);
    i=0;
    /**
    while(i<8)
    {
        printf("%d ",array[i]);
        i++;
    }
    printf("\n");*/
    j--;
    }

}

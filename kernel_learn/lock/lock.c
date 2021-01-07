#include "stdio.h"
#include "stdlib.h"
#define N 6
#define M 8
//参考C++函数构造随机置换
int myrandom(int i){
  if(i) return rand()%i;}
void swap(int *p,int *q)
{
    int temp;
    temp=*p;
    *p=*q;
    *q=temp;
    return ;
}
void myrandom_shuffle(int* vector, int n)
{
  int i;
  for (i=n-1; i>0; --i) {
    swap(&vector[i],&vector[myrandom(i+1)]);
  }
    return ;
}
void Construct_Max(const int *source,int Max[][M])
{
  int i,j,t;
  for(i=0;i<N;i++)
    {for(j=0;j<M;j++)
      {
      Max[i][j]=myrandom(source[j]);
      }
    }
     return ;

}
void Printf(const int Max[][M])
{   int i,j;
    for(i=0;i<N;i++)
    {for(j=0;j<M;j++)
      {printf("%d ",Max[i][j]);}
      printf("\n");}
      return ;
}
void Construct_Allocation(int Alloc[][M],const int Max[][M])
{
  int i,j;
  for(i=0;i<N;i++)
    for(j=0;j<M;j++)
      Alloc[i][j]=myrandom(Max[i][j]/3);
      return ;
}
void Compute_Need(const int Max[][M],const int Alloc[][M],int Need[][M])
{
  int i,j;
  for(i=0;i<N;i++)
    for(j=0;j<M;j++)
      Need[i][j]=Max[i][j]-Alloc[i][j];
      return ;
}
void Update_Avaiable(const int Alloc[][M],int * avaiable)
{
 int i,j;
 int temp[M]={0};
  for(j=0;j<M;j++)
    for(i=0;i<N;i++)
    temp[j]+=Alloc[i][j];
    for(i=0;i<M;i++)
    avaiable[i]-=temp[i];
    return;
}
int Checkout_Need(const int Need[][M])
{
 int i,j;
  for(i=0;i<N;i++)
    for(j=0;j<M;j++)
     if(Need[i][j]<0)
     return 1;
  
   return 0;
}
void Sercity_Check(int *sercity,int Need[][M],int Alloc[][M],int *avaiable)
{ 

  int t=0,i,j;
  int flag[N]={0};
  printf("进程序列：\n");
  while(t<N)
  {
  
  for(i=0;i<N;i++)
  { 
    if(flag[i]==0)
   {  j=0;
     for(;j<M&&(Need[i][j]<=avaiable[j]);j++); 
      if(j==M)
     {sercity[t]=i;
      flag[i]=1;
      printf("%d ",sercity[t]);
      for(int p=0;p<M;p++)
      avaiable[p]+=Alloc[i][p];
      t++;   
     break;
     }
   }  

  }

  }
  printf("\n");
}
int main()
{   

    int p1[8]={11,12,13,14,15,16,17,18};
    int p2[8]={10,10,10,11,12,13,14,17};
    int p3[8]={11,13,12,14,15,16,18,17};
    int p4[8]={17,16,18,12,14,17,18,11};
    int p5[8]={18,12,13,14,16,17,15,11};
    int *p[5]={p1,p2,p3,p4,p5};
    int Max[N][M]={0,0},Alloc[N][M]={0,0},Need[N][M]={0,0};
    int i,j=0;
    int sercity[N];
    int *q=sercity;
    /*初始化各种表格*/
    while(j<5)
    {

      /*step2*/
      Construct_Max(p[j],Max);

      /*step3*/
      Construct_Allocation(Alloc,Max);
      printf("init source:\n");
      for(int t=0;t<M;t++)
      printf("%d ",*(p[j]+t));
      printf("\n");
      /*step4*/
      Compute_Need(Max,Alloc,Need);

      Update_Avaiable(Alloc,p[j]);
    
      /*step5*/
      
      if(!Checkout_Need(Need))
      {
      printf("------MAX----\n");
      Printf(Max);
      printf("------Alloc----\n");
      Printf(Alloc);
      printf("------Need----\n");
      Printf(Need);
      printf("----Avaiable------\n");
      for(int t=0;t<M;t++)
      printf("%d ",*(p[j]+t));
      printf("\n");
      Sercity_Check(q,Need,Alloc,p[j]);
      j++;
      }
      /*step6*/
      //Sercity_Check(q,Need,Alloc,p[j-1]);
      }
      return 0;



}


/**
output:
init source:
11 12 13 14 15 16 17 18 
------MAX----
8 11 3 12 14 12 3 0
1 8 11 5 1 11 16 5 
3 2 4 4 6 12 9 9
6 10 1 12 8 7 7 0
9 6 10 4 2 11 1 12
4 3 5 9 3 8 11 7
------Alloc----
1 1 0 0 2 1 0 0
0 1 2 0 0 1 3 0 
0 0 0 0 0 2 1 2
0 1 0 2 1 0 1 0
1 0 0 0 0 0 0 0
0 0 0 1 0 0 1 0 
------Need----
7 10 3 12 12 11 3 0
1 7 9 5 1 10 13 5
3 2 4 4 6 10 8 7 
6 9 1 10 7 7 6 0
8 6 10 4 2 11 1 12
4 3 5 8 3 8 10 7 
----Avaiable------
9 9 11 11 12 12 11 16
进程序列：
2 3 0 1 4 5
init source:
10 10 10 11 12 13 14 17
------MAX----
1 8 4 0 2 0 7 16
8 2 9 8 9 6 5 10
4 0 7 7 5 0 9 15
4 2 0 10 5 12 1 5 
6 0 1 2 11 2 9 2
1 2 0 6 9 1 8 13
------Alloc----
0 1 0 0 0 0 1 2
1 0 2 1 0 1 0 1 
0 0 1 0 0 0 1 1 
0 0 0 0 0 0 0 0
0 0 0 0 2 0 1 0
0 0 0 1 0 0 1 0
------Need----
1 7 4 0 2 0 6 14
7 2 7 7 9 5 5 9
4 0 6 7 5 0 8 14 
4 2 0 10 5 12 1 5 
6 0 1 2 9 2 8 2
1 2 0 5 9 1 7 13
----Avaiable------
9 9 7 9 10 12 10 13
进程序列：
1 0 2 3 4 5
init source:
11 13 12 14 15 16 18 17 
------MAX----
4 9 9 4 5 3 2 7
9 7 9 6 9 4 4 2
4 1 7 0 8 4 8 5
5 10 1 8 13 15 9 13 
6 11 10 1 11 7 9 13
2 9 8 6 3 0 10 13
------Alloc----
0 1 2 0 0 0 0 1 
1 1 1 1 2 0 0 0
0 0 0 0 0 0 1 0
0 1 0 1 0 2 1 0
0 2 1 0 2 0 2 3
0 1 0 1 0 0 0 0
------Need----
4 8 7 4 5 3 2 6
8 6 8 5 7 4 4 2 
4 1 7 0 8 4 7 5
5 9 1 7 13 13 8 13
6 9 9 1 9 7 7 10 
2 8 8 5 3 0 10 13
----Avaiable------
10 7 8 11 11 14 14 13
进程序列：
1 0 2 3 4 5
init source:
17 16 18 12 14 17 18 11
------MAX----
12 8 2 10 0 5 11 4
14 4 12 5 8 3 3 0
4 5 0 4 1 9 2 4
11 11 13 5 2 5 15 9
1 10 1 2 9 7 16 6
8 8 8 5 12 0 17 0
------Alloc----
1 0 0 0 0 0 1 0
1 0 0 0 0 0 0 0
0 0 0 0 0 1 0 0 
1 1 1 0 0 0 3 2
0 0 0 0 1 0 0 0
0 1 0 0 1 0 1 0
------Need----
11 8 2 10 0 5 10 4
13 4 12 5 8 3 3 0
4 5 0 4 1 8 2 4
10 10 12 5 2 5 12 7
1 10 1 2 8 7 16 6 
8 7 8 5 11 0 16 0
----Avaiable------
14 14 17 12 12 16 13 9
进程序列：
0 1 2 3 4 5
init source:
18 12 13 14 16 17 15 11
------MAX----
7 2 4 1 3 7 13 10
8 8 2 1 12 16 13 7
10 1 10 12 14 6 1 2
2 1 1 4 11 10 9 5
8 6 0 13 9 11 3 8
14 8 4 13 1 6 11 5
------Alloc----
1 0 0 0 0 0 0 0
0 0 0 0 3 3 2 1
1 0 0 1 1 0 0 0
0 0 0 0 1 2 2 0
0 1 0 3 2 1 0 1
3 0 0 0 0 1 0 0
------Need----
6 2 4 1 3 7 13 10
8 8 2 1 9 13 11 6
9 1 10 11 13 6 1 2
2 1 1 4 10 8 7 5
8 5 0 10 7 10 3 7
11 8 4 13 1 5 11 5
----Avaiable------
13 11 13 10 9 10 11 9
进程序列：
4 3 0 1 2 5
*/
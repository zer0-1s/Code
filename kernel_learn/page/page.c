#include"stdio.h"
#include"stdlib.h"
#include "malloc.h"
#include "time.h"
#define instruct_num 320
#define MAX_INSTRUCT 10000
#define Page_Interrupt 100
typedef struct FIFO_Page
{
    int num;
    struct FIFO_Page * next;
}FIFO_Page;
typedef FIFO_Page *FIFO_Pageptr;
typedef struct Page
{
    int* p[10];
}Page;

int  Random_Offset(int m)
{ 
  //srand((unsigned)time(NULL)); // 发现放这里的化随机性会失效
  int temp;
  if(m!=0)
  temp=rand()%m;
  return temp;
}
int Mod_Num(int m)
{   if(m>=instruct_num)
    m=m%instruct_num;
    return m;
}

//构造可选指令集合
void Instruct_Addr_Imcomplment(int *instruct_addr)
{   
    int i=0;
    int m=Random_Offset(320);//choose num from 0-319
    while(i<320)
    {
    instruct_addr[Mod_Num(i)]=Mod_Num(m+1);//instruct[i]=m+1
    i++;
    int m1=Random_Offset(m+2);//choose from 0-m+1 ,so input %(m+2)
    instruct_addr[Mod_Num(i)]=Mod_Num(m1);//instruct[i]=m1   
    i++;
    instruct_addr[Mod_Num(i)]=Mod_Num(m1+1);//instruct[i]=m1+1
    i++;
    int m2=Mod_Num(m1+2)+Random_Offset(instruct_num-m1-2);//m1+2-319 choose random num
    instruct_addr[Mod_Num(i)]=Mod_Num(m2);//instruct[i]=m2
    i++;
    instruct_addr[Mod_Num(i)]=Mod_Num(m2+1);//instruct[i]=m2+1
    i++;
    m=Mod_Num(m2+1);//m=m2+1
    }
}
void Instruct_Virtual_Page(Page* Newpage,int * instruct)
{

  for(int i=0;i<320;i++)
    {   
        Newpage[(instruct[i])/10].p[(instruct[i])%10]=&instruct[i];
    }
    return ;
}
//我的理解顺序访问320条指令，但是其存储在虚拟页面（32k）,10页,每个页面10条指令,要通过一定的页面置换算法来载入内存
int * Instruct_Addr()
{  
    int *instruct_addr=(int*)malloc(instruct_num*sizeof(int));
    //memset(instruct_addr,0,sizeof(int)*instruct_num);
    Instruct_Addr_Imcomplment(instruct_addr);
    return instruct_addr;

}
void swap(int * a, int * b)
{
    int temp;
    temp=*(a);
    *(a)=*(b);
    *(b)=temp;
   // printf("%d ",*(b)/10);
}
// OPT算法的具体实现,传入的页号为(*(instruct[i])/10)
void  Get_Maxoffset(int*temp,int *Pagenum,int t,int memsize)
{
    int offset,i=0,j,count;
    int memflag[memsize],flag=0;
    int temp2;//中间的中介变量
    int Max=0;
    while(i<memsize)
    {
    for(int j=t;j<320;j++)
    { 
    if((Pagenum[j])==temp[i])
    {
    memflag[i]=j-t;
    break;
    }
    if(j==320)
    {
    memflag[i]=500;//means not found
    flag=1;
    }
    }
    i++;
    }
    i=i-memsize;//to save space
    if(flag==1)
    {while(i<memsize)
    {
    if(memflag[i]==500)
    temp[i]=Pagenum[t];
    //swap(&temp[i],&Pagenum[t]);//内存块中存在没访问的页面的交换 
    i++;
    }
    }


    if(flag==0)
    {
    while(i<memsize)
    {
    if(memflag[i]>Max)
    {
    Max=memflag[i];
    temp2=i;
    }
    i++;
    }
    temp[temp2]=Pagenum[t-1];
    //swap(&temp[i],&Pagenum[t]);//正常交换页面
    }
    return ;
}
// 访问的页面数是320,取值从0到31之间,目标计算缺页中断的次数,Pagenum=Instruct
int OPT_Replace(int *Pagenum,int memsize)
{   

    int conut=0;//记录缺页中断的次数,当扫描完memsize发现没有就纪录一次缺页中断
    int t=0,f,h,j;
    int temp[memsize];//代表实际的内存块，以k为单位
    int temp2;//页面交换的中介   
    while(t<memsize)
    {
    temp[t]=Pagenum[t];
    t++;
    }
    conut+=memsize;
    while(t<320)
    {
    for(j=0;j<memsize;j++)
    {
    if(temp[j]==(Pagenum[t]))//是否本就驻留内存
         break;
    }
    if(j==memsize)
   {
    Get_Maxoffset(temp,Pagenum,t+1,memsize);//没有驻留内存进行交换
    conut++;
   }
    t++;
    }
    return conut;
}
//实现memsize的链表结构,反映出标号
void FIFO_LIST(int *Pagenum,int memsize,int t)
{
    FIFO_Pageptr L,p,q,temp,nL;
    /*init FIFO_LIST*/
    L=(FIFO_Pageptr)malloc(sizeof(FIFO_Page));
    L->num=Pagenum[0];
    p=L;
    for(int i=1;i<memsize;i++)
    {
    q=p;
    p=(FIFO_Pageptr)malloc(sizeof(FIFO_Page));
    p->num=Pagenum[i];
    q->next=p;
    }
    p->next=NULL;
    /*look up elem in FIFO_LIST*/
    temp=L;
    while(Pagenum[t]!=temp->num)
    temp=temp->next;
    /*change ptr relationship*/
    if(temp==NULL)
    {
    /*add tail node*/
    temp=(FIFO_Pageptr)malloc(sizeof(FIFO_Page));
    temp->num=Pagenum[t];
    temp->next=NULL;
    /*change head node */
    nL=L;
    L=L->next;
    free(nL);
    }
}
// FIFO的算法有一个特征即：从上到下依次置换内存,当然这也与第一次调入内存是有关,即可以简化,即采用一种不用链表也可以实现的方法
int FIFO_Replace(int *Pagenum,int memsize)
{
    int conut=0;//记录缺页中断的次数,当扫描完memsize发现没有就纪录一次缺页中断
    int t=0,f,h,j;
    int temp[memsize];//代表实际的内存块，以k为单位
    int temp2;//页面交换的中介
    int turn=0;
    while(t<memsize)
    {
    temp[t]=Pagenum[t];
    t++;
    }
    conut+=memsize;
    while(t<320)
    {
    for(j=0;j<memsize;j++)
    {
    if(temp[j]==(Pagenum[t]))//是否本就驻留内存
         break;
    }
    if(j==memsize)
   {
    //Get_Maxoffset(temp,Pagenum,t+1,memsize);//没有驻留内存进行交换
    temp[turn]=Pagenum[t];
    turn++;
    turn=turn%memsize;
    conut++;
   }
    t++;
    }
    return conut;

}
void  LRU_offset(int*temp,int *Pagenum,int t,int memsize)
{

    int offset,i=0,j,count;
    int memflag[memsize];
    int temp2;//中间的中介变量
    int Max=0;
    while(i<memsize)
    {
    for(int j=t;j>=0;j--)
    { 
    if((Pagenum[j])==temp[i])
    {
    memflag[i]=t-j;
    break;
    }
    }
    i++;
    }
    i=i-memsize;//to save space
    for(int j=0;j<memsize;j++)
    {
    if(memflag[j]>=Max)
    {
    Max=memflag[j];
    temp2=j;
    }
    }
    temp[temp2]=Pagenum[t+1];
    //swap(&temp[i],&Pagenum[t]);//正常交换页面
    
    return ;

}

int LRU_Replace(int *Pagenum,int memsize)
{

    int conut=0;//记录缺页中断的次数,当扫描完memsize发现没有就纪录一次缺页中断
    int t=0,f,h,j;
    int temp[memsize];//代表实际的内存块，以k为单位
    int temp2;//页面交换的中介
    int turn=0;
    while(t<memsize)
    {
    temp[t]=Pagenum[t];
    t++;
    }
    conut+=memsize;
    while(t<320)
    {
    for(j=0;j<memsize;j++)
    {
    if(temp[j]==(Pagenum[t]))//是否本就驻留内存
         break;
    }
    if(j==memsize)
   {
    //Get_Maxoffset(temp,Pagenum,t+1,memsize);//没有驻留内存进行交换
    LRU_offset(temp,Pagenum,t-1,memsize);
    conut++;
   }

    t++;
    }
    return conut;
}
void Convet_to_Page(Page *Newpage,int *q[])
{
for(int i=0;i<320;i++)
q[i]=Newpage[i/10].p[i%10];
return;
}
int main()
{   
    srand((unsigned)time(NULL));
    int Pagesize[29];
    Page Newpage[32];
    int *p,*r,turn=0;
    int temp[320];
    int** q;
    int opt_count,fifo_count,lru_count;
    double opt_target=0.0,fifo_target=0.0,lru_target=0.0;
    /*init Pagesize*/
    for(int i=0;i<29;i++)
    Pagesize[i]=i+4;
    while(turn++<10)
   { /*construct instruct[]*/
    p=Instruct_Addr();
    /*convert to virtual page*/
    Instruct_Virtual_Page(Newpage,p);
    //Convet_to_Page(Newpage,q);
    for(int i=0;i<320;i++)
    {temp[i]=p[i]/10;
    }
    r=temp;
    opt_count=OPT_Replace(r,10);
    opt_target+=(float)opt_count/320;
    fifo_count=FIFO_Replace(r,10);
    fifo_target+=(float)fifo_count/320;
    lru_count=LRU_Replace(r,10);
    lru_target+=(float)lru_count/320;
    }
    printf("OPT %lf  ",(1.0-opt_target/10));
    printf("FIFO:%lf  ",(1.0-fifo_target/10));
    printf("LRU:%lf  ",(1.0-lru_target/10));
    return 0;

}
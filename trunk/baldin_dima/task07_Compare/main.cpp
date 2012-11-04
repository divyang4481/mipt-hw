#include <iostream>
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <cstdio>
using namespace std;

void Random(int *a,int n)
{
    srand (time (NULL));
    for(int i=0;i<n;++i)
     a[i]=rand();
}
void CopyBuf(int *a,int *b,int n)
{
    for(int i=0;i<n;++i)
     b[i]=a[i];
}
bool Check(int *a,int n)
{
   for (int i=0;i<n-1;++i)
    if (a[i]>a[i+1])
    return (false);
   return(true) ;
}
int Compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

void InsertSort(int n,int *buf)
{
    int x;
    for (int i=1;i<n;i++)
    {
      x=buf[i];int j=i-1;
      for (j=i-1;(j>=0)&&(buf[j]>x);--j)
       {
         buf[j+1]=buf[j];

       }
      buf[j+1]=x;
    }
}

void Merge(int* buf,int* help,int l,int m,int r)
{

    int countl=l,countr=m+1,counth=0;
    for (int k=0;k<=(r-l);++k)
    {
        if ((countl<=m)&&(countr<=r))

            if (buf[countl]<buf[countr])
            {
                help[counth]=buf[countl];
                ++counth;
                ++countl;
            }
            else
            {
                help[counth]=buf[countr];
                ++counth;
                ++countr;
            }

        else
            if (countl>m)
                {
                 for (int j=countr;j<=r;++j)
                  help[counth++]=buf[j];
                 break;
                }

            else
                {
                 for (int j=countl;j<=m;++j)
                  help[counth++]=buf[j];
                 break;
                }
      }

    for (int i=l;i<=r;++i)
     buf[i]=help[i-l];

};
void MergeSort(int* buf,int* help,int l,int r)
{
    if (l<r)
    {
        int m=(l+r)/2;
        MergeSort(buf,help,l,m);
        MergeSort(buf,help,m+1,r);
        Merge(buf,help,l,m,r);
    }
};

void QuickSort(int l, int r, int *buf)
{
    int i=l,j=r,k=(l+r)/2,x=buf[k];
    do
    {
     while (buf[i]<x) ++i;
     while (buf[j]>x) --j;
     if (i<=j)
     {
         int b=buf[i];
         buf[i]=buf[j];
         buf[j]=b;
         ++i;--j;
     }
    }
    while (i<=j);
    if (i<r) QuickSort(i,r,buf);
    if (j>l) QuickSort(l,j,buf);
}

void insert(int *buf,int num_of_elem,int n)
{
    int new_elem;
    new_elem=buf[num_of_elem];
    int cur_num;
    while (num_of_elem<=n/2)
    {
        cur_num=2*num_of_elem;
        if ((cur_num<n)&&(buf[cur_num]<buf[cur_num+1]))
         ++cur_num;
        if (new_elem>=buf[cur_num]) break;
        buf[num_of_elem]=buf[cur_num];
        num_of_elem=cur_num;
    }
    buf[num_of_elem]=new_elem;
}
void HeapSort(int *buf, int n)
{
  int b;
  for (int i=n/2;i>=0;i--)
     insert(buf,i,n-1);
  for (int i=n-1;i>0;i--)
  {
      b=buf[i];buf[i]=buf[0];buf[0]=b;
      insert(buf,0,i-1);
  }
}

int kolb(int a)
{
    int q=1,b=0;
    while (a!=0)
    {
        a=a/2;

        ++b;
    }
    return b;
}
void RadixSort(int* buf,int n,int k)
{


    int* k0;
    int* k1;
    k0=(int*)malloc(n*sizeof(int));
    k1=(int*)malloc(n*sizeof(int));

    for (int i=0;i<k;++i)
    {

        k0[0]=0;k1[0]=0;
        for (int j=0;j<n;++j)
        if ((abs(buf[j])&(1<<i))==0)
        {
            ++k0[0];
            k0[k0[0]]=buf[j];
        }
        else
        {
            ++k1[0];
            k1[k1[0]]=buf[j];
        }
        for (int z=0;z<k0[0];++z)
         buf[z]=k0[z+1];
        for (int z=0;z<k1[0];++z)
         buf[k0[0]+z]=k1[z+1];

    }

   free(k0);
   free(k1);
}

int main()
{

    int n,t,t1;
    cin >> n;
    int *buf,*help,*helptomerge;
    buf=(int*)malloc(n*sizeof(int));
    help=(int*)malloc(n*sizeof(int));
    helptomerge=(int*)malloc(n*sizeof(int));
    Random(buf,n);



    ////qsort
    CopyBuf(buf,help,n);
    t=clock();
    qsort((void*)help, n, sizeof(int), Compare);
    t1 = clock();
    cout << "qsort = "<< (t1 - t) << "\n";

    ////insertsort
    CopyBuf(buf,help,n);
    t=clock();
    InsertSort(n,help);
    t1 = clock();
    if (Check(help,n)==true)
    cout << "InsertSort = "<< (t1 - t) << "  true"<< "\n";
    else {
           cout << "false";
           return(0);
         }

    ////mergesort
    CopyBuf(buf,help,n);
    t=clock();
    MergeSort(help,helptomerge,0,n-1);
    t1 = clock();
    if (Check(help,n)==true)
    cout << "MergeSort = "<< (t1 - t) << "  true"<< "\n";
    else {
           cout << "false";
           return(0);
         }

    ////quicksort
    CopyBuf(buf,help,n);
    t=clock();
    QuickSort(0,n-1,help);
    t1 = clock();
    if (Check(help,n)==true)
    cout << "QuickSort = "<< (t1 - t) << "  true"<< "\n";
    else {
           cout << "false";
           return(0);
         }

    ////heapsort
    CopyBuf(buf,help,n);
    t=clock();
    HeapSort(help,n);
    t1 = clock();
    if (Check(help,n)==true)
    cout << "HeapSort = "<< (t1 - t) << "  true"<< "\n";
    else {
           cout << "false";
           return(0);
         }

    ////radixsort
    CopyBuf(buf,help,n);
    int max=0;
    for (int i=0;i<n;++i)
     {
         if (max<abs(help[i])) max=abs(help[i]);
     }
    t=clock();
    RadixSort(help,n,kolb(max));
    t1 = clock();
    if (Check(help,n)==true)
    cout << "RadixSort = "<< (t1 - t) << "  true"<< "\n";
    else {
           cout << "false";
           return(0);
         }


    return 0;
}

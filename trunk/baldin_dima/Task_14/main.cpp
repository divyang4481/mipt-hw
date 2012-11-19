#include <iostream>
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <cstdio>
using namespace std;

int Part(int *buf,int p, int r)
{
    int x = buf[r];
    int i = p-1;
    for (int j=p;j<r;++j)
      if (buf[j]<=x)
        {
            i++;
            swap(buf[i],buf[j]);
        }
    swap(buf[i+1], buf[r]);
    return i+1;
}
int Rand_Part(int *buf, int p,int r)
{
    int i = rand()%(r-p)+p;
    swap(buf[r],buf[i]);
    return Part(buf,p,r);
}
int Rand_Sel(int *buf, int p, int r, int i)
{
    if (p==r)
    return buf[p];
    int q = Rand_Part(buf,p,r);
    int k = q-p+1;
    if (i == k)
    return(buf[q]);
    else if (i<k)
         return Rand_Sel(buf, p, q-1,i);
         else return Rand_Sel(buf, q+1, r, i-k);

}
void QuickSort(int l, int r, int *buf)
{
    int i=l,j=r,k=rand()%(r-l)+l,x=buf[k];
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
int main()
{
    srand(time(NULL));
    int n,k;
    cin >> n;
    cin >> k;
    int *buf=(int*)malloc(n*sizeof(int));
    for (int i=0; i<n; i++)
     cin >> buf[i] ;
    cout << Rand_Sel(buf,0,n-1,k);
    free(buf);
    return 0;
}

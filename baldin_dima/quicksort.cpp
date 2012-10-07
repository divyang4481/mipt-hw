#include <iostream>
#include <stdlib.h>
using namespace std;


void sort(int l, int r, int *buf)
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
    if (i<r) sort(i,r,buf);
    if (j>l) sort(l,j,buf);
}
int main()
{
    int *buf;
    int n;
    cin >> n;
    buf=(int*)malloc(n*sizeof(int));
    for (int i=0;i<n;++i)
     cin >> buf [i];
    sort(0,n-1,buf);
    for (int i=0;i<n;++i)
     cout << buf[i] << ' ';
    free(buf);
    return 0;
}

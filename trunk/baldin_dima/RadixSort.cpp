#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <algorithm>
using namespace std;


int kolB(int a)
{
    int b=0;
    while (a!=0)
     {
         a=a/2;
         ++b;
     }
    return b;
}
void RadixSort(int* buf,int n,int b)
{
   int k1,k2;
   for (int i=0;i<b;++i)
    {

      int f=0;
      do
      {

      f=0;
      for (int j=1;j<n;++j)
      {
        k1=abs(buf[j-1])&(1<<i);
        k2=abs(buf[j])&(1<<i);
        if (k1>k2)
        {swap(buf[j-1],buf[j]);
         f=1;
        }
      }
      }
      while (f==1);


    }
}
int main()
{
    int n;
    cin >> n;
    int* buf;
    buf=(int*)malloc(n*sizeof(int));
    int MAX=0;
    for (int i=0;i<n;++i)
       {
           cin >> buf[i];
           MAX=max(MAX,abs(buf[i]));
       }
    RadixSort(buf,n,kolB(MAX));
    for (int i=n-1;i>=0;--i)
     if (buf[i]<0) cout << buf[i] << ' ';
    for (int i=0;i<n;++i)
     if (buf[i]>=0) cout << buf[i] << ' ';


    return 0;
}

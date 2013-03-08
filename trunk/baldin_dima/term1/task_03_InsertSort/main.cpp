#include <iostream>
#include <stdlib.h>
using namespace std;

void insert(int n,int *buf)
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
int main()
{
    int *buf;
    int n;
    cin >> n;
    buf=(int*)malloc(n*sizeof(n));
    for (int i=0;i<n;++i)
     cin >> buf[i];
    insert(n, buf);
    for (int i=0;i<n;++i)
     cout << buf [i] << ' ';
    free (buf);
    return 0;
}

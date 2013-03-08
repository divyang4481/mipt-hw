#include <iostream>
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <cstdio>
using namespace std;

int K_static(int l, int r, int *buf, int ks)
{
    int i = l,j = r,k = rand()%(r - l + 1) + l, x = buf[k];
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
    if ((l <= ks) && ( ks <= j)) K_static(l, j, buf, ks);
    if ((i <= ks) && (ks <= r)) K_static(i, r, buf, ks);
    return buf[ks];
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
    cout << K_static(0, n-1, buf, k-1);
    free(buf);
    return 0;
}


#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;


void Merge(int* buf,int* help, int l,int m,int r)
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
void MergeSort(int* buf,int *help,int l,int r)
{
    if (l<r)
    {
        int m=(l+r)/2;
        MergeSort(buf,help,l,m);
        MergeSort(buf,help,m+1,r);
        Merge(buf,help,l,m,r);
    }
};
void MergeToStart(int* buf, int n)
{
    int *help=(int*)malloc((n)*sizeof(int));
    MergeSort(buf, help, 0, n-1);
    free(help);
}
int main ()
{
    freopen("input.txt","r",stdin);
    int n;
    cin >> n;
    int *buf=(int*)malloc(n*sizeof(int));
    for (int i=0;i<n;++i)
     cin >> buf[i];
    MergeToStart(buf,n);
    for (int i=0;i<n;++i)
     cout << buf[i] << ' ';
    free(buf);
    return(0);
}

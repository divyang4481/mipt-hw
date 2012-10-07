#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

void tomerge (int l1,int r1,int l2,int r2,int *buf)
{

    int *help;
    help=(int*)malloc((r1-l1)*sizeof(int));
    for (int i=l1;i<=r1;++i)
    {
     help[i-l1]=buf[i];
    }
    int k=0,j=l2,tek=l1;
    while ((k<=r1-l1)&&(j<=r2))
    {
        if (help[k]<buf[j])
        {
            buf[tek]=help[k];
            k++;

        }
        else
        {
           buf[tek]=buf[j];

           j++;
        }
        tek++;
    }
    for (int i=k;i<=r1-l1;i++)
    {
        buf[tek]=help[i];
        tek++;
    }
    for (int i=j;i<=r2;i++)
    {
        buf[tek]=buf[i];
        tek++;
    }
   free(help);
}
void merge (int l,int r, int *buf)
{
    if (l==r) {}
    else
    {
        merge(l,(l+r)/2,buf);
        merge((l+r)/2+1,r,buf);
        tomerge(l,(l+r)/2,(l+r)/2+1,r, buf);

    }
}

int main ()
{
    int *buf;
    int n;

    cin >> n;
    buf=(int*)malloc(n*sizeof(int));
    for (int i=0;i<n;++i)
     cin >> buf[i];
    merge(0,n-1,buf);
    for (int i=0;i<n;++i)
     cout << buf[i] << ' ';
    free(buf);
    return(0);
}

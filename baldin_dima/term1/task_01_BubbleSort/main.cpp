#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

void swap (int &a,int &b)
{
    int t=a;
    a=b;
    b=t;
}

void bubble(int *buf,int n)
{
    int f;
    do
    {
        f=1;
        for (int i=0;i<n-1;++i)
        {
            if (buf[i]>buf[i+1])
            {
                swap(buf[i],buf[i+1]);
                f=0;
            }
        }

    n--;
    }
    while (f==0);

}

int main()
{
int* ptd;
int n;
cin >> n;
ptd = (int *)malloc(n * sizeof(int));
for (int i=0;i<n;++i)
 cin >> ptd[i];
bubble(ptd,n);
for (int i=0;i<n;++i)
 cout << ptd[i] << ' ';
free(ptd);
return 0;

}

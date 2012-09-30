//

#include "cstdio"
#include "stdafx.h"

int BubbleSort(int l, int r, int* a)
{
    for (int i=r-1;i>l;--i)
    {
        for (int j=0; j<i; ++j)
        {
            if (a[j]>a[j+1])
            {
                int t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
    return 0;
}  

int main()
{
    int N=0;
    scanf("%d\n",&N);
    int* Ar=new int[N];
    for (int i=0; i<N; ++i)
        scanf("%d",Ar+i);
    BubbleSort(1,N,Ar);
    for (int i=0; i<N; ++i)
        printf("%d ",Ar[i]);    
    return 0;
}


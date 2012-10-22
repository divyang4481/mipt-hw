#include <cstdio>

int BubbleSort(int* a, int r)
{
    for (int i=0 ; i<r; ++i)
    {
        for (int j=r-1; j>=i; --j)
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

int QuickSort(int* a, int b, int f)
{
    if (b<f)
    {
        int l=b, r=f;
        int x=a[(l+r)/2];
        while (l<=r)
        {
            while (a[l]<x) ++l;
            while (a[r]>x) --r;
            if (l<=r)
            {
                if (l<r)
                {
                    int tmp=a[l];
                    a[l]=a[r];
                    a[r]=tmp;
                }
                ++l;
                --r;
            }
        }
        QuickSort(a,b,r);
        QuickSort(a,l,f);
        return 0;
    }
}

int main()
{
    int N=0;
    scanf("%d\n",&N);
    int* Ar=new int[N];
    for (int i=0; i<N; ++i)
        scanf("%d",Ar+i);
    Bub;
    for (int i=0; i<N; ++i)
        printf("%d ",Ar[i]);  
    delete[] Ar;
    return 0;
}


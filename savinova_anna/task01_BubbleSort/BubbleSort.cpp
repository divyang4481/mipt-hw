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

int main()
{
    int N=0;
    scanf("%d\n",&N);
    int* Ar=new int[N];
    for (int i=0; i<N; ++i)
        scanf("%d",Ar+i);
    BubbleSort(Ar, N);
    for (int i=0; i<N; ++i)
        printf("%d ",Ar[i]);  
    delete[] Ar;
    return 0;
}


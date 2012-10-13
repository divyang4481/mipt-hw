// QuickSort.cpp: определяет точку входа для консольного приложения.
//

#include "cstdio"

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
    scanf("%d",&N);
    int* A=new int[N];
    for (int i=0; i<N; ++i)
        scanf("%d",(A+i));
    QuickSort(A,0,N-1);
    for (int i=0; i<N; ++i)
        printf("%d ",A[i]);
    delete[] A;
    return 0;
}


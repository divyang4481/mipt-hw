// MergeSort.cpp: определяет точку входа для консольного приложения.
//

#include <cstdio>

void Merge(int* a, int l, int q, int r)
{
    if ((r-l)>1)
    {
        int* b=new int [r-l+1];
        int k=0, i=l, j=q+1;
        for ( ; (i<=q) && (j<=r); ++k)
        {
            if (a[i]<a[j])
            {

                b[k]=a[i];
                ++i;
            }
            else 
            {
                b[k]=a[j];
                ++j;
            }
        }
        if (i<=q)
            for ( ; i<=q; ++i, ++k)
                b[k]=a[i];
        else if (j<=r)
                for ( ; j<=r; ++j, ++k)
                    b[k]=a[j];
        for (int i=l; i<=r; ++i)
            a[i]=b[i-l];
        delete[] b;
    }
    else if (a[l]>a[r])
    {
            int t=a[l];
            a[l]=a[r];
            a[r]=t;
    }
}

void MergeSort(int* a, int l, int r)
{
    if (l>=r) return;
    else
    {
        int q=(l+r)/2;
        MergeSort(a,l,q);
        MergeSort(a,q+1,r);
        Merge(a,l,q,r);
    }
}


int main()
{
    int N=0;
    scanf("%d ",&N);
    int* A=new int [N+2];
    for (int i=0; i<N; ++i)
        scanf("%d",(A+i));
    MergeSort(A,0,N-1);
    for (int i=0; i<N; ++i)
        printf("%d ",A[i]);
    delete[] A;
    return 0;
}

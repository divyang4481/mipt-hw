// QuickSort.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "cstdio"

int QuickSort(int* A , int b, int c)
{
    if (b<c)
    {
        int l=b, r=c;
        int x=A[(l+r)/2];
        while (l<=r)
        {
            while (A[l]<x) ++l;
            while (A[r]>x) --r;
            if (l<=r)
            {
                if (l<r)
                {
                    int t=A[l];
                    A[l]=A[r];
                    A[r]=t;
                }
                ++l;
                --r;
            }
        }
        QuickSort(A,b,r);
        QuickSort(A,l,c);
        return 0;
    }
}
int main()
{
	int N=0;    
    scanf("%d",&N);
    int* Ar=new int[N];
    for (int i=0; i<N; ++i)
        scanf("%d",(Ar+i));
    QuickSort(Ar,0,N-1);
    for (int i=0; i<N; ++i)
        printf("%d ",Ar[i]);
    delete[] Ar;
    return 0;
}
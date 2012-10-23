// Task07.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <time.h>
#include <iostream>

using namespace std;


double BubbleSort(int* a, int r)
{
    time_t start,end;
    time (&start);
    for (int i=0 ; i<r; ++i)
    {
        for (int j=r-2; j>=i; --j)
        {
            if (a[j]>a[j+1])
            { 
                int t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
    time (&end);
    return difftime(end, start);
}

double QuickSort(int* a, int b, int f)
{
    time_t start,end;
    time (&start);
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
        time (&end);
        return difftime(end, start);
    }
}

double InsertSort(int* a, int l, int r)
{
    for (int j=l+1; j<r; ++j)
    {
        int key=a[j], i=j-1;
        while ((i>l-1) && (a[i]>key))
        {
            a[i+1]=a[i];
            --i;
        }
        a[i+1]=key;
    }
    time (&end);
    return difftime(end, start);
}

bool Cor(int* a, int la)
{
    for (int i=0; i<la-1; ++i)
        if (a[i]>a[i+1])
            return false;
    return true;
}

int main()
{
    srand(time(NULL));
    int N=0;
    cin>>N;
    int* A=new int[N];
    int* B=new int[N];
    for (int i=0; i<N; ++i)
    {
        A[i]=rand();//%(2*RAND_MAX) + (-RAND_MAX);
        B[i]=A[i];
    }
    time_t start,end;
    time (&start);
    /*double t = */BubbleSort(B, N);
    time (&end);
    double t=difftime(end, start);
    cout<<"BubbleSort "<<t<< "sdf";
    if (Cor(B,N))
        cout<<" true"<<endl;
    else cout<<" false"<<endl;
    for (int i=0; i<N; ++i)
    {
        B[i]=A[i];
    }
    t = QuickSort(B, 0, N-1);
    cout<<endl;
    cout<<"QuickSort "<<t;
    if (Cor(B,N))
        cout<<" true"<<endl;
    else cout<<" false"<<endl;
    for (int i=0; i<N; ++i)
    {
        B[i]=A[i];
    }
    t = InsertSort(B, 0, N);
    cout<<"InsertSort "<<t;
    if (Cor(B,N))
        cout<<" true"<<endl;
    else cout<<" false"<<endl;
    for (int i=0; i<N; ++i)
    {
        B[i]=A[i];
    }
    delete[] A;
    delete[] B;
    return 0;
}
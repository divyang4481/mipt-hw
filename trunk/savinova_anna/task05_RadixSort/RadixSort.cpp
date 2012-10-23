// RadixSort.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int** CreateMatr(int w, int h)
{
    
    int** buf=new int*[h];
    for (int i=0; i<h; ++i)
    {
        *(buf+i)=new int[w];
    }
    return buf;
}

int** CopyMatr(int** a, int w, int h)
{
    int** b=CreateMatr(w,h);
    for (int i=0; i<h; ++i)
    {
        for (int j=0; j<w; ++j)
        {
            b[i][j]=a[i][j];
        }
    }
    return b;
}

void WriteMatr(const int* const* buf, int w, int h)
{
    for (int i=0; i<h; ++i)
    {
        for (int j=0; j<w; ++j)
        {
            cout<<buf[i][j]<<" ";
        }
        cout<<endl;
    }
}

int CountingSort(int** a, int la, int** &b, int k)
{
    int c[10];
    for (int i=0; i<=9; ++i)
        c[i]=0;
    for (int i=0; i<la; ++i)
        ++c[a[i][k]];
    for (int i=1; i<=9; ++i)
        c[i]+=c[i-1];
    for (int j=la-1; j>=0; --j)
    {
        b[c[a[j][k]]-1]=a[j];
        --c[a[j][k]];
    }
    return 0;
}
int RadixSort(int* a, int la)
{
    int d=0;
    int max=A[1];
    for (int i=0; i<N; ++i)
        if (A[i]>max)
            max=A[i];
    for (int i=1; i<max; i*=10, ++d);
    int** m=CreateMatr(d,la);
    int** n=CreateMatr(d,la);
    for (int i=0; i<la; ++i)
        for (int j=0; j<d; ++j)
        {
            m[i][j]=a[i]%10;
            a[i]/=10;
        }
    for (int i=0; i<d; ++i)
    {
        CountingSort(m,la,n,i);
        m=CopyMatr(n,d,la);
    }
    for (int i=0; i<la; ++i)
        for (int j=0, k=1; j<d; ++j, k*=10)
            a[i]+=m[i][j]*k;
    return 0;
}

int main()
{
    int N=0;
    cin>>N;
    int* A=new int[N];
    int D=0;
    for (int i=0; i<N; ++i)
        cin>>A[i];
    int MAX=A[1];
    for (int i=0; i<N; ++i)
        if (A[i]>MAX)
            MAX=A[i];
    for (int i=1; i<MAX; i*=10, ++D);
    RadixSort(A,N);
    for (int i=0; i<N; ++i)
        cout<<A[i]<<" ";
    delete[] A;
    return 0;
}
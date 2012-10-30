// Task07.cpp: определяет точку входа для консольного приложения.
//
#include "StdAfx.h"
#include <time.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class THeap {
private:
    int* Buf;
    int Size;
    
    int Parent(int idx) {
        return((idx - 1) / 2);
    }

    int Left(int idx) { 
        return(idx + idx + 1);
    }

    int Right(int idx) {
        return(idx + idx + 2);
    }

    void BuildHeap() {
        for(int i = Parent(Size - 1); i >= 0; --i)
            Heapify(i);
    }

    void Heapify(int idx) {
        int max = idx, l = Left(idx), r = Right(idx);
        if ((l < Size) && (Buf[idx] < Buf[l]))
            max = l;
        if ((r < Size) && (Buf[max] < Buf[r]))
            max = r;
        if (max != idx) {
            swap(Buf[idx], Buf[max]);
            Heapify(max);
        }
    }

public:
    THeap(int* buf, int size) {
        Buf = buf;
        Size = size;
        BuildHeap();
    }
    
    void Print() {
        for(int i = 0; i < Size; ++i)
            cout << Buf[i] << ' ';
    }

    int Max() {
        return Buf[0];
    }

    int ExtractMax() {
        int m = Buf[0];
        --Size;
        swap(Buf[0], Buf[Size]);
        Heapify(0);
        return m;
    }

    int GetSize() {
        return(Size);
    }

    const int* GetBuf() {
        return Buf;
    }

    void Insert(int elem) {      
        ++Size;
        int num = Size-1, p = Parent(num);
        Buf[num] = elem;
        while ((Buf[num] > Buf[p]) && (num > 0)) {
            if (Buf[num] > Buf[p]) {
                swap(Buf[num], Buf[p]);
                num = p;
            }
        }
    }

    void Delete(int idx) {
        --Size;
        swap(Buf[idx], Buf[Size]);
        Heapify(Parent(idx));
    }
};

int BubbleSort(int* a, int r)
{
    for (int i = 0 ; i < r; ++i)
    {
        for (int j = r - 2; j >= i; --j)
        {
            if (a[j] > a[j+1])
            { 
                int t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }
    return 0;
}

int InsertSort(int* a, int l, int r)
{
    for (int j = l + 1; j < r; ++j)
    {
        int key = a[j], i = j - 1;
        while ((i > l - 1) && (a[i] > key))
        {
            a[i+1] = a[i];
            --i;
        }
        a[i+1] = key;
    }
    return 0;
}

int QuickSort(int* a, int b, int f)
{
    if (b < f)
    { 
        int l = b, r = f;
        int x = a[(l + r) / 2];
        while (l <= r)
        {
            while (a[l] < x) ++l;
            while (a[r] > x) --r;
            if (l <= r)
            {
                if (l < r)
                {
                    int tmp = a[l];
                    a[l] = a[r];
                    a[r] = tmp;
                }
                ++l;
                --r;
            }
        }
        QuickSort(a, b, r);
        QuickSort(a, l, f);
    }
    return 0;
}

int** CreateMatr(int w, int h)
{
    
    int** buf = new int*[h];
    for (int i = 0; i < h; ++i)
    {
        *(buf + i)=new int[w];
    }
    return buf;
}

int** CopyMatr(int** a, int w, int h)
{
    int** b = CreateMatr(w, h);
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            b[i][j] = a[i][j];
        }
    }
    return b;
}

void DeleteMatr(int** buf, int w, int h)
{
    for (int i = 0; i < h; ++i)
    {
        delete[] *(buf + i);
    }
    delete[] buf;
}

int CountingSort(int** a, int la, int** &b, int k)
{
    int c[10];
    for (int i = 0; i <= 9; ++i)
        c[i] = 0;
    for (int i = 0; i < la; ++i)
        ++c[a[i][k]];
    for (int i = 1; i <= 9; ++i)
        c[i] += c[i-1];
    for (int j = la - 1; j >= 0; --j)
    {
        b[c[a[j][k]]-1] = a[j];
        --c[a[j][k]];
    }
    return 0;
}

int RadixSort(int* a, int la)
{
    int d = 0;
    int max = a[1];
    for (int i = 0; i < la; ++i)
        if (a[i] > max)
            max = a[i];
    for (int i = 1; i < max; i *= 10, ++d);
    int** m = CreateMatr(d, la);
    int** n = CreateMatr(d, la);
    for (int i = 0; i < la; ++i)
        for (int j = 0; j < d; ++j)
        {
            m[i][j] = a[i] % 10;
            a[i] /= 10;
        }
    for (int i = 0; i < d; ++i)
    {
        CountingSort(m, la, n, i);
        m=CopyMatr(n, d, la);
    }
    for (int i = 0; i < la; ++i)
        for (int j = 0, k = 1; j < d; ++j, k *= 10)
            a[i] += m[i][j] * k;
    DeleteMatr(m, d, la);
    DeleteMatr(n, d, la);
    return 0;
}

int HeapSort(int* a, int len) {
    THeap h(a, len);
    for (int i = len-1; i > 0; --i)
        h.ExtractMax();
    return 0;
}

int Cor(int* a, int la)
{
    for (int i = 0; i< la - 1; ++i)
    {
        if (a[i] > a[i+1])
        {
            cout << " false" << endl;
            return 0;
        }
    }
    cout << " true" << endl;
    return 0;
}

int Compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

long long Clock() 
{
    return clock() * 1000 / CLOCKS_PER_SEC;
}


int main()
{
    srand(time(NULL));
    int N = 0;
    cin >> N;
    int* A = new int[N];
    int* B = new int[N];
    for (int i = 0; i < N; ++i)
    {
        A[i] = rand();
        B[i] = A[i];
    }
    long long t = Clock();
    BubbleSort(B, N);
    long long t1 = Clock() - t;
    cout << "BubbleSort " << t1 << " ms";
    Cor(B, N);
    for (int i = 0; i < N; ++i)
    {
        B[i] = A[i];
    }
    t = Clock();
    InsertSort(B, 0, N);
    t1 = Clock() - t;
    cout << "InsertSort " << t1 << " ms"; 
    Cor(B, N);
    for (int i = 0; i < N; ++i)
    {
        B[i] = A[i];
    }
    t = Clock();
    QuickSort(B, 0, N-1);
    t1 = Clock()-t;
    cout << "QuickSort "<< t1 <<" ms";
    Cor(B, N);
    for (int i = 0; i < N; ++i)
    {
        B[i] = A[i];
    }
    t = Clock();
    RadixSort(B, N);
    t1 = Clock() - t;
    cout << "RadixSort " << t1 << " ms";
    Cor(B, N);
    for (int i = 0; i < N; ++i)
    {
        B[i] = A[i];
    }
    t = Clock();
    qsort((void*)B, N, sizeof(int), Compare);
    t1 = Clock() - t;
    cout<< "qsort "<< t1 <<" ms";
    Cor(B, N);
    for (int i = 0; i < N; ++i)
    {
        B[i] = A[i];
    }
    t = Clock();
    HeapSort(B, N);
    t1 = Clock()-t;
    cout <<"HeapSort "<< t1 <<" ms";
    Cor(B, N);
    delete[] A;
    delete[] B;
    return 0;
}
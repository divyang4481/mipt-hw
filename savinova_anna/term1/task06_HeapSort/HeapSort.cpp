#include <stdlib.h>

#include <math.h>

#include <stdio.h>

#include <iostream>

using namespace std;


class THeap {
private:
    int* Buf;
    int Size; //������ �������
    
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
    /*~THeap()
    {
        printf("Delete/n");
        delete[] Buf;
    };*/

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

int HeapSort(int* a, int len) {
    THeap h(a, len);
    for (int i = len-1; i > 0; --i)
        h.ExtractMax();
    return 0;
}

int main() {
    int N = 0;
    cin >> N;
    int* A = new int[N];
    for (int i = 0 ; i < N; ++i)
        cin >> A[i];
    HeapSort(A, N);
    for (int i = 0; i < N; ++i)
        cout << A[i] << ' ';
    delete[] A;
    return 0;
}
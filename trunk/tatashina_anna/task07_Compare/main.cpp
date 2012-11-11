#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iomanip>
#include <time.h>
#include <algorithm>

using namespace std;

bool check(int n, int *a)
{
    for (int i = 1; i < n; ++i) 
        if (a[i] < a[i - 1]) 
                        return(false);
    return(true);
}

void Random(int n, int *a) {
        for(int i = 0; i < n; ++i)
                a[i] = rand();
}
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}
void Bubble_sort(int N, int *a) {
        for (int i = 0; i < N; ++i)
                for (int j = 0; j < N - 1; ++j)
                        if (a[j] > a[i])
                                swap(a[i], a[j]);
}

void merge(int left, int mid, int right, int *a, int *temp){
    int i1 = 0;
    int i2 = left;
    int i3 = mid + 1;
 
    while ((i2 <= mid) && (i3 <= right)){
        if (a[i2] < a[i3])
            temp[i1++] = a[i2++];
        else
            temp[i1++] = a[i3++];
    }
    while (i2 <= mid)
        temp[i1++] = a[i2++];
    while (i3 <= right)
        temp[i1++] = a[i3++];
 
    for(int i = left; i <= right; ++i)
        a[i] = temp[i - left];
 
} 
void MergeSort(int left, int right, int *a, int *temp){
    if (left < right){
        int mid = (left + right) / 2;
        MergeSort(left, mid, a, temp);
        MergeSort(mid + 1, right, a, temp);
        merge(left, mid, right, a, temp);
    }
}

void InsertSort(int left, int right, int *a) {
        int buf;
        int j;
        for (int i = left; i < right; i++) {
                buf = a[i];
                for (j = i - 1; ((j >= 0) && (a[j] > buf)); j--) {
                        a[j + 1] = a[j];
                }
                a[j + 1] = buf;
        }
}

void QSort(int left, int right, int *a) {
        int m = a[(left + right) / 2];
        int i = left;
        int j = right;
        do {
                while (a[i] < m) 
                        i++;
                while (a[j] > m)
                        j--;
                if (i <= j) {
                        swap(a[i], a[j]);
                        i++;
                        j--;
                }
        }while (i <= j);
        if (left < j)
                QSort(left, j, a);
        if (i < right)
                QSort(i, right, a);
}

int findD(int *a, int N) {
        int D;
        int max;
        D = 0;
        max = a[0];
        for (int i = 0; i < N; i++) 
                if (a[i] > max) {
                        max = a[i];
                        
                }

        while (max)
        {
                D++;
                max /= 10;
        }


        return D;
}
void RadixSort(int *a, int N) {
        int D;
        D = findD(a, N);
    int *b = (int*) malloc(N*sizeof(int));      
        int c[10];
        int q = 1;

        for (int i = 0; i < D; i++) {
                for (int j = 0; j < 10; j++)
                        c[j] = 0;

                for (int j = 0; j < N; j++)
                        c[(a[j] / q) % 10]++;

                for (int j = 1; j < 10; j++)
                        c[j] = c[j] + c[j - 1];

                for (int j = 0; j < 10; j++) 
                        c[j]--;

                for (int j = N - 1; j >= 0; j--) {
                        b[c[(a[j] / q) % 10]] = a[j];
                        c[(a[j] / q) % 10]--;
                }
                for (int j = 0; j < N; j++) 
                        a[j] = b[j];

                q *= 10;
        } 
}
void AllRadix(int *a, int N) {
        int *b = (int*) malloc(N*sizeof(int));
        int *c = (int*) malloc(N*sizeof(int));
        int n1 = 0, n2 = 0;
        for(int i = 0; i < N; i++)
                if (a[i] > 0)
                        b[n1++] = a[i];
                else
                        c[n2++] = -a[i];
        RadixSort(b, n1);
        RadixSort(c, n2);
        for(int i = 0; i < n2; i++)
                a[i] = -c[n2 - i - 1];
        for(int i = 0; i < n1; i++)
                a[n2 + i] = b[i];
    
        free(b);
		free(c);
}
void copy(int*a, int*b, int n) {
	for(int i = 0; i < n; ++i)
		a[i] = b[i];
}

class THeap {
        private:
                int*Buf;
                int Size;
           
            int Parent(int idx) {
              return((idx- 1)/2);
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
                THeap(int*buf, int size) {
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


                int GetSize() {
                        return(Size);
                }

                const int* GetBuf() {
                        return Buf;
                }

                void DecSize() {
                        Size--;
                }
                void HeapSort(int* a, int n) {
                        for (int i = GetSize(); i > 0; i--) {
                                swap(a[0], a[i - 1]);
                                DecSize();                              
                                Heapify(0);
                        }
                }

};

int main()
{
        srand (time (NULL));
        int n;
        cin >> n;
        cout << fixed << setprecision(5);
        int *a = (int*) malloc(n*sizeof(int));
        int *b = (int*) malloc(n*sizeof(int));

        Random(n, a);
		copy(b, a, n);

        ///////////////////////////////
        float now = clock();
        Bubble_sort(n, a);
        now  = float(clock() - now)/CLOCKS_PER_SEC;
		if (check(n, a))
                cout << "Bubble_sort = "<< now << " c\n";
        else 
                cout << "Bubble_sort failed";

		copy(a, b, n);
        ///////////////////////////////

        ///////////////////////////////
        now = clock();
		int *temp = (int*) malloc((n + 1)*sizeof(int));
        MergeSort(0, n - 1, a, temp);
        now  = float(clock() - now)/CLOCKS_PER_SEC;        
		if (check(n, a))        
                cout << "Merge_sort = "<< now << " c\n"; 
        else 
                cout << "Merge_sort failed";

        free(temp);
		copy(a, b, n);
        ///////////////////////////////

        ///////////////////////////////
        now = clock();
        InsertSort(0, n, a);
	    now  = float(clock() - now)/CLOCKS_PER_SEC;    
        if (check(n, a))        
                cout << "Insert_sort = "<< now << " c\n";
        else 
                cout << "Insert_sort failed";
		copy(a, b, n);
        /////////////////////////////// 

        ///////////////////////////////
        now = clock();
        QSort(0, n - 1, a);
        now  = float(clock() - now)/CLOCKS_PER_SEC;    
        if (check(n, a))        
                cout << "Qsort = "<< now << " c\n";
        else 
                cout << "Qsort failed";
		copy(a, b, n);
		///////////////////////////////

        ///////////////////////////////
        now = clock();
		qsort((void*)a, n, sizeof(int), compare);
        now  = float(clock() - now)/CLOCKS_PER_SEC;    
		if (check(n, a))        
                cout << "CQsort = "<< now << " c\n";
        else 
                cout << "CQsort failed";
		copy(a, b, n);
		///////////////////////////////

        ///////////////////////////////
        now = clock();
        AllRadix(a, n);
	    now  = float(clock() - now)/CLOCKS_PER_SEC;   
        if (check(n, a))        
                cout << "RadixSort = "<< now << " c\n";
        else 
                cout << "RadixSort failed";     
		copy(a, b, n);
        /////////////////////////////// 
        
        ///////////////////////////////
        now = clock();
		THeap h(a, n);
		h.HeapSort(a, n);
	    now  = float(clock() - now)/CLOCKS_PER_SEC; 
        if (check(n, a))
                cout << "Heap_Sort = "<< now << " c\n";
        else 
                cout << "Heap_Sort failed";     
        /////////////////////////////// 
        free(b);
        free(a);

        return(0);

}
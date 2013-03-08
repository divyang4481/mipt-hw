#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

using namespace std;


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

int main() {
	int n;
	int *a;
	cin >> n;
	a = (int*)malloc(n*sizeof(int));
    for (int i = 0 ; i < n; ++i)
        cin >> a[i];
    
	THeap h(a, n);
	h.HeapSort(a, n);
	
	for (int i = 0; i < n; ++i)
		cout << a[i] << " ";

	free(a);
	return 0;
}

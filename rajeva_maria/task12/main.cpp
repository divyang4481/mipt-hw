
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iomanip>
#include <time.h>
#include <algorithm>

using namespace std;

class THeap {
        private:
                double* Buf;
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

                void SiftUp(int idx) {
					if (idx)
						if (Buf[idx] < Buf[Parent(idx)]) {
							swap(Buf[idx], Buf[Parent(idx)]);
							SiftUp(Parent(idx));
						}
				}
				void SiftDown(int idx) {
					if (Right(idx) < Size) {
						if (Left(idx) >= Size) {
							if (Buf[idx] > Buf[Right(idx)]) {
								swap(Buf[idx], Buf[Right(idx)]);
								SiftDown(Right(idx));
							}
						}
						else
							if (min(Buf[Left(idx)], Buf[Right(idx)]) < Buf[idx])
								if (Buf[Left(idx)] > Buf[Right(idx)]) {
									swap(Buf[idx], Buf[Right(idx)]);
									SiftDown(Right(idx));
								}
								else {
									swap(Buf[idx], Buf[Left(idx)]);
									SiftDown(Left(idx));
								}
					}
				}
				void Heapify(int idx) {
					SiftUp(idx);
					SiftDown(idx);
				}
        public:
                THeap(double* buf, int size) {
                        Buf = buf;
                        Size = size;
                        BuildHeap();
                }
    
                void Print() {
                        for(int i = 0; i < Size; ++i)
                                cout << Buf[i] << ' ';
                }

                double Min() {
                        return Buf[0];
                }


                int GetSize() {
                        return(Size);
                }

                const double* GetBuf() {
                        return Buf;
                }

                void DecSize() {
                        Size--;
                }

                void HeapSort(double* a, int n) {
                        for (int i = GetSize(); i > 0; i--) {
                                swap(a[0], a[i - 1]);
                                DecSize();                              
                                Heapify(0);
                        }
                }
				void Delete(int idx) {
					swap(Buf[Size - 1], Buf[idx]);
					DecSize();
					Heapify(idx);
				}
				void Delete_Min() {
					Delete(0);
				}
				void Insert(double f) {
					Buf[Size++] = f;
					Heapify(Size - 1);
				}
};

double Kahansum(double *a, int n)
{
	double y=0.0;
	double t=0.0;
	double sum=0.0;
	double c=0.0;
	for (int i = 0; i < n; i++)
	{
		y = a[i] - c;
		t = sum + y;
		c = (t - sum) - y;
		sum = t;
	}
	return sum;
}

double Heapsum(double *a, int n)  
{
	THeap heap = THeap(a, n);
	for(int i = 0; i < n - 1; ++i)
	{
		double sum = heap.Min();
		heap.Delete_Min();
		sum =sum+heap.Min();
		heap.Delete_Min();
		heap.Insert(sum);		
	}
	return a[0];
}

int main() {
    int N;
	cin >> N;	
    double *Ar, *A;
    Ar = (double*)malloc(N*sizeof(double));
	A = (double*)malloc(N*sizeof(double));
	for(int i = 0; i < N; ++i)
	{
		cin >> Ar[i];
		A[i] = Ar[i];
	}
	cout << Heapsum(Ar, N) ;
	cout<<" ";
	cout << Kahansum(A, N);
	free(Ar);
	free(A);
	system("pause");
	return 0;
}
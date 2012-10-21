#include <iostream>
using namespace std;

class THeap{
private:
    int *Buf;
    int Size;
    int Parent(int idx){
        return (idx-1)/2;
    }
    int Left(int idx)
    {
        return (idx+idx+1);
    }
    int Right(int idx)
    {
        return (idx+idx+2);
    }
    void Heapify(int idx, int n)
    {
        int max=idx, l=Left(idx), r=Right(idx);
        if ((l<n) && (Buf[idx]<Buf[l])) max=l;
        if ((r<n) && (Buf[max]<Buf[r])) max=r;
        if (max!=idx) 
        {
            swap(Buf[idx],Buf[max]);
            Heapify(max,n);
        }
    }
    void BuildHeap(){
        for (int i=Parent(Size-1); i>=0; --i) Heapify(i,Size);
    }


public:
    THeap (int *buf, int size){
        Buf=buf;
        Size=size;
        BuildHeap();
    }
    void Print(){
        for (int i=0; i<Size; ++i) printf("%d ",Buf[i]);
    }
    int Max()
    {
        return Buf[0];
    }
    int GetSize()
    {
        return Size;
    }
    const int* GetBuf()
    {
        return Buf;
    }
    void Insert(int elem)
    {
        
    }
    void Delete(int idx)
    {

    }	
	void HeapSort()
	{
		int n=Size;
		while (n>1)
		{
			--n;
			int t=Buf[0];
			Buf[0]=Buf[n];
			Buf[n]=t;
			Heapify(0,n);
		}
	}
};

int main()
{
    int n;
    scanf("%d",&n);
    int *A=new int [n];
    for (int i=0; i<n; ++i) A[i]=rand()%100;
	for (int i=0; i<n; ++i) printf("%d ",A[i]);
	printf("\n");
    THeap h(A,n);
	h.HeapSort();
	h.Print();
    return 0;
}
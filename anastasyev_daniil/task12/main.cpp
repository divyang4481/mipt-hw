#include <iostream>
#include <time.h>
#include <cstdio>
using namespace std;

class THeap{
private:
    float *Buf;
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

    void BuildHeap(){
        for (int i=Parent(Size-1); i>=0; --i) Heapify(i,Size);
    }
public:
    THeap (float *buf, int size){
        Buf = buf;
        Size=size;
        BuildHeap();
    }
    void Print(){
        for (int i=0; i<Size; ++i) printf("%f ",Buf[i]);
    }
    float Max()
    {
        return Buf[0];
    }
    int GetSize()
    {
        return Size;
    }
    const float* GetBuf()
    {
        return Buf;
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
	float ExtractMax()
	{
		if (Size<1) return 0;
		float max = Buf[0];
		Buf[0] = Buf[Size-1];
		--Size;
		Heapify(0, Size);
		return max;
	}
	void Insert(float k)
	{
			++Size;
			int i=Size-1;
			while ((i>0) && (Buf[Parent(i)]<k)) 
			{
				Buf[i] = Buf[Parent(i)];
				i = Parent(i);
			}
			Buf[i] = k;
	}
};

int main()
{
    int n;
    scanf("%d",&n);
    float c=0., sum=0.;
    float *f = new float[n];
	for (int i=0; i<n; ++i) scanf("%f",(f+i));
	int time = clock(); 
    for (int i=0; i<n; ++i)
    {
        float y = f[i] - c;
        float t = sum + y;
        c = (t - sum) - y;   
        sum = t; 
    }
    time = clock() - time;
    printf("%.7f %f\n",sum,(float)time/CLOCKS_PER_SEC);
	THeap p(f, n);
	time = clock();
	if (n>1)
		for (int i=0; i<n-1; ++i)
		{
			float f1 = p.ExtractMax();
			float f2 = p.ExtractMax();
			f1 += f2;
			p.Insert(f1);
		}
	time = clock() - time;
	printf("%.7f %f",p.Max(),((float)time)/CLOCKS_PER_SEC);
	delete [] f;
    return 0;
}

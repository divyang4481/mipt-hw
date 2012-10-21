#include <iostream>
#include <time.h>
using namespace std;

void BubbleSort(int *a, int N)
{
     for (int i=0; i<N-1; ++i) 
     {
         for (int j=N-2; j>=i; --j)
         {
             if (a[j]>a[j+1]) {swap(a[j],a[j+1]);}
         }
     }  
}

void swap1(int &a, int &b)
{
	if (a>b)
	{
		int t=a;
		a=b;
		b=t;
	}
}

int Min(int *a, int &i, int &j)
{
	int t;
	if (a[i]<a[j]) 
	{
		t=a[i];
		i+=1;
	}
	else 
	{
		t=a[j];
		j+=1;
		
	}
	return t;
}

void Merge(int *a, int l, int m, int r, int *c)
{
	
	int i=l, j=m+1;
	int k=0;
	while ((i<=m) && (j<=r))
	{
		c[k]=Min(a,i,j);
		++k;
	}
	if (i<=m) 
	{
		for (j=i; j<=m; ++j, ++k) c[k]=a[j];
	}
	else
	{
		for (i=j; i<=r; ++i, ++k) c[k]=a[i];
	}
	for (i=l, k=0; i<=r; ++i, ++k) a[i]=c[k];
}

void MergeSort(int *a, int l, int r, int *c)
{
	int m;
	if (r-l<1) {}
	else 
	{if (r-l==1)
	{
		swap1(a[l],a[r]);
	}
	else 
	{
		m=(l+r)/2;
		MergeSort(a,l,m,c);
		MergeSort(a,m+1,r,c);
		Merge(a,l,m,r,c);
	}
	}
}

void MERGESORT(int *a, int n)
{
    int *c= new int[n];
    MergeSort(a,0,n-1,c);
}

void InsertSort(int *a, int n)
{
	for (int i = 1; i < n; ++i) 
	{
        int t = a[i];
		int j=i-1;
		while ((j>=0) && (a[j]>t))
		{
                a[j+1] = a[j];
                a[j]= t;
				j-=1;
        }
 
	}
}

void qsort(int* a, int l, int r)
{
    int i = l, j = r, x = a[(l + r) / 2];
	while (i <= j)
    {
        while (a[i] < x) i++;
        while (a[j] > x) j--;
 
        if (i <= j) 
		{
            swap(a[i], a[j]);
            i++; j--;
        }
    } 
	
	if (l < j) qsort(a, l, j); 
    if (i < r) qsort(a, i, r);

}

int** Create(int h, int w)
{
    
    int** b=new int*[h];
    for (int i=0; i<h; ++i)
    {
        *(b+i)=new int[w];
    }
    return b;
}

int** Copy(int** a, int h, int w)
{
    int** b=Create(h,w);
    for (int i=0; i<h; ++i)
    {
        for (int j=0; j<w; ++j)
        {
            b[i][j]=a[i][j];
        }
    }
    return b;
}

void Delete(int **a, int h, int w)
{
    for (int i=0; i<h; ++i) delete [] a[i];
    delete [] a;
}

void CountSort(int **c, int **b, int k, int n)
{   
    int count[10];
    for (int i=0; i<=9; ++i) count[i]=0;
    for (int i=0; i<n; ++i) ++count[c[i][k]];
    for (int i=1; i<=9; ++i) count[i]+=count[i-1];
    for (int i=n-1; i>=0; --i)
    {
        b[count[c[i][k]]-1]=c[i];
        --count[c[i][k]];
    }
}

void RadixSort(int *a, int n)
{
	int MAX=a[0];
    int d=0;
	for (int i=0; i<n; ++i) if (a[i]>MAX) MAX=a[i];
	while (MAX) {MAX/=10; ++d;}
	int **c=Create(n,d);
	int **b=Create(n,d);
	for (int i=0; i<n; ++i) 
    {
		for (int j=0; j<d; ++j) {c[i][j]=a[i]%10; a[i]/=10;}
	}
	for (int i=0; i<d; ++i) 
    {
        CountSort(c,b,i,n);
        c=Copy(b,n,d);
    }
    for (int i=0; i<n; ++i)
        for (int j=0, k=1; j<d; ++j, k*=10) a[i]+=c[i][j]*k;
    Delete(c,n,d);
    Delete(b,n,d);
}

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

bool proverka(int *a, int n)
{
    for (int i=1; i<n; ++i) 
        if (a[i]<a[i-1]) return 0;
    return 1;
}

int * copy(int *b, int n)
{
    int *a= new int [n];
    for (int i=0; i<n; ++i) a[i]=b[i];
    return a;
}

int main()
{
    int n;
    int t, t1;
	scanf("%d",&n);
	int *a=new int[n];
    int *b=new int[n];
    for (int i=0; i<n; ++i) {*(a+i)=rand(); *(b+i)=*(a+i);}
    t=clock();
    BubbleSort(a,n);
    t1=clock()-t;
    if (proverka(a,n)) printf("BubbleSort verno za %d",t1);
    else printf("BubbleSort neverno");
    a=copy(b,n);
    printf("\n");

    t=clock();
    MERGESORT(a,n);
    t1=clock()-t;
    if (proverka(a,n)) printf("MergeSort verno za %d",t1);
    else printf("MergeSort neverno");
    a=copy(b,n);
    printf("\n");

    t=clock();
    InsertSort(a,n);
    t1=clock()-t;
    if (proverka(a,n)) printf("InsertSort verno za %d",t1);
    else printf("InsertSort neverno");
    a=copy(b,n);   
    printf("\n");

    t=clock();
    qsort(a,0,n-1);
    t1=clock()-t;
    if (proverka(a,n)) printf("QuickSort verno za %d",t1);
    else printf("QuickSort neverno");
    a=copy(b,n); 
    printf("\n");

    t=clock();
    RadixSort(a,n);
    t1=clock()-t;
    if (proverka(a,n)) printf("RadixSort verno za %d",t1);
    else printf("RadixSort neverno");
    a=copy(b,n); 
    printf("\n");

    t=clock();
    THeap h(a,n);
	h.HeapSort();
    t1=clock()-t;
    if (proverka(a,n)) printf("HeapSort verno za %d",t1);
    else printf("HeapSort neverno");
    a=copy(b,n); 

	delete [] a;
    delete [] b;
	return 0;
}
#include "cstdio"
#include "iostream"
using namespace std;
void swap(int &a, int &b)
{ int temp = a; a=b; b= temp; }
void heapify(int *A, int i,int heap_size)
{ int left=2*i,right=2*i+1;
	int largest=i;
	if (left<=heap_size && A[left]>A[i]) largest=left;
	if (right<=heap_size && A[right]>A[largest]) largest=right;
	if (largest!=i) {
		swap(A[i],A[largest]);
		heapify(A,largest, heap_size); }
}
void build_heap(int *A, int n)
{for (int i=n/2;i>=1;i--) heapify(A,i,n);
}
void heap_sort(int *A, int n)
{
	int heap_size=n;
	for (int i=n;i>=1;i--) {swap(A[1],A[i]); heap_size--; heapify(A,1,heap_size);}
}
int main()
{	int n;
    scanf("%d",&n);
	int*a=new int [n+1];
	a[0]=-1;
	for (int i=1;i<n+1;i++) 
	scanf("%d",&a[i]);
	build_heap(a,n);
	heap_sort(a,n);
	for (int i=1;i<n+1;i++)
	printf("%d ",a[i]);
	delete[](a);
	system("pause");
}

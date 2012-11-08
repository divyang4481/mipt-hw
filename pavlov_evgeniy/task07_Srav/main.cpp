#include"functions.h"
#include<iostream>
#include<time.h>
using namespace std;
void rav(int *a,int *b,int n)
{
	for(long i=0;i<n;++i)b[i]=a[i];
}
int main()
{
	int t,*a,*b;
	long n;
	cin>>n;
	a=new int[n];
	b=new int[n];
	for(long i=0;i<n;++i)a[i]=rand()%60000-10000;
	rav(a,b,n);
	t=clock();
	BubbleSort(b,n);
	cout<<"bubble-"<<clock()-t<<'\n';
	rav(a,b,n);
	t=clock();
	msort(b,n);
	cout<<"merge-"<<clock()-t<<'\n';
	rav(a,b,n);
	t=clock();
	insertsort(b,n);
	cout<<"insert-"<<clock()-t<<'\n';
	rav(a,b,n);
	t=clock();
	quicksort(b,0,n-1);
	cout<<"quick-"<<clock()-t<<'\n';
	rav(a,b,n);
	t=clock();
	radixs(b,n);
	cout<<"radix-"<<clock()-t<<'\n';
	rav(a,b,n);
	t=clock();
	Heapsort(b,n);
	cout<<"heap-"<<clock()-t<<'\n';
	return 0;
}
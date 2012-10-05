#include<iostream>
using namespace std;
void swap(int *a,int m,int n)
{
	int k=a[m];a[m]=a[n];a[n]=k;
}
void quicksort(int *a,int b,int e)
{
	int m=a[(b+e)/2];
	int b1=b,e1=e;
	do
	{
		while(a[b1]<m)++b1;
		while(a[e1]>m)--e1;
		if(e1>=b1){swap(a,e1,b1);++b1;--e1;}
	}
	while(e1>b1);
	if(e1>b)quicksort(a,b,e1);
	if(b1<e)quicksort(a,b1,e);
}
int main()
{
	int n,*a;
	cin>>n;
	a=new int[n];
	for(int i=0;i<n;++i)cin>>a[i];
	quicksort(a,0,n-1);
	for(int i=0;i<n;++i)cout<<a[i]<<" ";
	delete[]a;
	return 0;
}
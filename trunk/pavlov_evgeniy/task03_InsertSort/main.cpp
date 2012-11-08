#include<iostream>
using namespace std;
void insertsort(int *a,int n)
{
	for(int i=1;i<n;++i)
		for(int j=i-1;(j>-1)&&(a[j+1]<a[j]);--j)
		swap(a[j],a[j+1]);
}
int main()
{
	int n,*a;
	cin>>n;
    a=new int[n];
	for(int i=0;i<n;++i)cin>>a[i];
	insertsort(a,n);
	for(int i=0;i<n;++i)cout<<a[i]<<" ";
	delete[] a;
	return 0;
}
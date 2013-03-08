#include<iostream>
using namespace std;
int main()
{
	long long *a;
	unsigned int n;
	cin>>n;
	a=new long long[n+1];
	a[0]=1;
	for(unsigned int i=1;i<=n;++i)
	{
		a[i]=0;
		for(unsigned int j=0;j<i;++j)a[i]+=a[j]*a[i-1-j];
	}
	cout<<a[n];
	delete[] a;
	return 0;
}
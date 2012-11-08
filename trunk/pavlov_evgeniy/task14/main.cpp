#include<iostream>
using namespace std;
long random(long n)
{
    return rand()%n;
}
void qu(long *a,long b,long e,long k)
{
	if(e-b>1)
	{
		long r=b+random(e-b+1);
		long m=a[r],bb=b,ee=e;
		while(bb<ee)
		{
			while(a[bb]<m)++bb;
			while(a[ee]>m)--ee;
			swap(a[bb],a[ee]);
		}
		if(k<=bb)qu(a,b,bb,k);else qu(a,bb,e,k);
	}
	else
	{
		if(a[e]<a[b])swap(a[e],a[b]);
		cout<<a[k-1];
	}
}
int main()
{
	long n,k,*a;
	cin>>n>>k;
	a=new long[n];
	for(long i=0;i<n;++i)cin>>a[i];
	qu(a,0,n-1,k);
	return 0;
}
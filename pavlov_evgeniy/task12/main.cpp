#include<iostream>
#include<time.h>
#include<iomanip>
using namespace std;
float kah(float *a,long n)
{
	float sum=0,c=0,t,y;
	for(long i=0;i<n;++i)
	{
		y=a[i]-c;
		t=sum+y;
		c=(t-sum)-y;
		sum=t;
	}
	return sum;
}
void heap(float *a,long k,long l,long n)
{
	if((a[2*k+1]<a[k])&&((2*k+2>n-1)||(a[2*k+1]<=a[2*k+2])))
	{swap(a[k],a[2*k+1]);if(2*k+1<=l)heap(a,2*k+1,l,n);}
	else if((a[2*k+2]<a[k])&&(2*k+2<=n-1))
	{swap(a[k],a[2*k+2]);if(2*k+2<=l)heap(a,2*k+2,l,n);}
}
void str(float *a,long n)
{
	for(long i=(n-2)/2;i>=0;--i)heap(a,i,(n-2)/2,n);
}
float sum(float *a,long n)
{
	str(a,n);
	while(n>2)
	{
		swap(a[0],a[n-1]);
		heap(a,0,(n-3)/2,n-1);
		a[0]+=a[n-1];
		heap(a,0,(n-3)/2,n-1);
		--n;
	}
	if(n=2)return (float)a[0]+a[1];else return a[0];
}
int main()
{
	long n;
	int t;
	cin>>n;
	float o;
	float *a=new float[n];
	for(long i=0;i<n;++i)cin>>a[i];
	t=clock();
	o=kah(a,n);
	cout<<fixed<<setprecision(7)<<o<<" time "<<clock()-t<<'\n';
	t=clock();
	o=sum(a,n);
	cout<<fixed<<setprecision(7)<<o<<" time "<<clock()-t<<'\n';
	return 0;
}
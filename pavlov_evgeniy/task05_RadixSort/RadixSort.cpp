#include<iostream>
using namespace std;
void radixs(int *a,int n)
{
	int m=1,ma=10;
	int *o=new int[n];
	for(int i=0;i<n;++i)while(a[i]>=ma){++m;ma=ma*10;}
	int b[10],c[10];
    ma=10;
	for(int i=0;i<m;++i)
	{ for(int j=0;j<10;++j)b[j]=0;
		for(int j=0;j<n;++j)++b[(a[j]%ma)/(ma/10)];
		c[0]=0;
		for(int j=1;j<10;++j)c[j]=c[j-1]+b[j-1];
		for(int j=0;j<n;++j){o[c[(a[j]%ma)/(ma/10)]]=a[j];++c[(a[j]%ma)/(ma/10)];}
		ma=ma*10;
		for(int j=0;j<n;++j)a[j]=o[j];
	

	}
	delete[]o;
}
int main()
{
	int n,*a;
	cin>>n;
	a=new int[n];
	for(int i=0;i<n;++i)cin>>a[i];
	radixs(a,n);
	for(int i=0;i<n;++i)cout<<a[i]<<' ';
	delete[]a;
	return 0;
}
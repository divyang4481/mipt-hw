#include<iostream>
using namespace std;
void radixs(int *a,int n)
{
	int m=1,ma=10;
	int *o=new int[n];
	for(int i=0;i<n;++i)while(abs(a[i])>=ma){++m;ma=ma*10;}
	int b[19],c[19];
    ma=10;
	for(int i=0;i<m;++i)
	{   
		for(int j=0;j<19;++j)b[j]=0;
		for(int j=0;j<n;++j)++b[(a[j]%ma)/(ma/10)+9];
		c[0]=0;
		for(int j=1;j<19;++j)c[j]=c[j-1]+b[j-1];
		for(int j=0;j<n;++j){o[c[(a[j]%ma)/(ma/10)+9]]=a[j];++c[(a[j]%ma)/(ma/10)+9];}
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
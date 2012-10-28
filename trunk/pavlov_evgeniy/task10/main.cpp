#include<iostream>
using namespace std;
int main()
{
 int n,*a,*b;
 cin>>n;
 a=new int[n+1];
 b=new int[n+1];
 a[1]=1;a[0]=1;
 for(int i=2;i<n+1;++i)
 {
	 b[0]=1;b[i]=1;for(int j=1;j<i;++j)b[j]=a[j-1]+a[j];
	 swap(a,b);
 }
 for(int i=0;i<n+1;++i)cout<<a[i]<<' ';
 return 0;
}


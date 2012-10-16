#include<iostream>
using namespace std;
void merge(int *a,int b,int e,int *c,int k,int m,int k1)
{
	for(int i=0;i<e-b+1;++i)if(k>>m){c[i]=a[k1];++k1;}
	else{if(k1>e){c[i]=a[k];++k;}
	else{if(a[k]<a[k1]){c[i]=a[k];++k;}else{c[i]=a[k1];++k1;}
	}
	}
	for(int i=0;i<e-b+1;++i)a[b+i]=c[i];
}
void mergesort(int *a,int b,int e,int *c)
{ 
	if(e-b>0)
	{
		int m=(e+b)/2;
		mergesort(a,b,m,c);
		mergesort(a,m+1,e,c);
	}
		merge(a,b,e,c,b,(e+b)/2,(e+b)/2+1);

}
int main()
{
	int *c;
	int n;
	cin>>n;
	int *a=new int[n];
	c=new int[n];
	for(int i=0;i<n;++i)cin>>a[i];
	mergesort(a,0,n-1,c);
	for(int i=0;i<n;++i)cout<<a[i]<<" ";
	delete[] a;
	delete[] c;
	return 0;
}
#include<iostream>
using namespace std;
void merge(int *a,int b,int e)
{
	int m=(e+b)/2;
	int *c=new int[e-b+1];
	int k=b;
	int k1=m+1;
	for(int i=0;i<e-b+1;++i)if(k>>m){c[i]=a[k1];++k1;}
	else{if(k1>e){c[i]=a[k];++k;}
	else{if(a[k]<a[k1]){c[i]=a[k];++k;}else{c[i]=a[k1];++k1;}
	}
	}
	for(int i=0;i<e-b+1;++i)a[b+i]=c[i];
	delete[] c;
}
void mergesort(int *a,int b,int e)
{ 
	if(e-b>0)
	{
		int m=(e+b)/2;
		mergesort(a,b,m);
		mergesort(a,m+1,e);
	}
		merge(a,b,e);

}
int main()
{
	int n;
	cin>>n;
	int *a=new int[n];
	for(int i=0;i<n;++i)cin>>a[i];
	mergesort(a,0,n-1);
	for(int i=0;i<n;++i)cout<<a[i]<<" ";
	delete[] a;
	return 0;
}

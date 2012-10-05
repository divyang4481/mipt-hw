#include<iostream>
#include<time.h>
using namespace std;
void BubbleSort(int *m,int s)
{for(int i=0;i<s;++i)
	for(int j=i+1;j<s;++j)
		if (m[j]<m[i]){
			int k;k=m[i];m[i]=m[j];m[j]=k;}
}
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
void swap(int *a,int b,int c)
{
	int k=a[b];
	a[b]=a[c];a[c]=k;
}
void insertsort(int *a,int n)
{
	for(int i=1;i<n;++i)
		for(int j=i-1;(j>-1)&&(a[j+1]<a[j]);--j)
		swap(a,j+1,j);
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
	int n;
	cout<<"vvedite razmer massiva"<<'\n'<<"(ne rekomenduetsya vvodit' chisla prevyshayushie 30000)"<<'\n';
	cin>>n;
	int *a=new int[n],*b=new int[n];
	for(int i=0;i<n;++i){
		a[i]=rand()%1000+1;
	}
	b=a;
	int t1,t2,t3,t4,t;
	t=clock();
	BubbleSort(b,n);
	t1=clock()-t;
	b=a;
	mergesort(b,0,n-1);
	t2=clock()-t1-t;
	b=a;
	insertsort(b,n);
	t3=clock()-t1-t2-t;
	b=a;
	quicksort(b,0,n-1);
	t4=clock()-t1-t2-t3-t;
	delete[] a,b;
	cout<<"buble "<<t1<<'\n'<<"merge "<<t2<<'\n'<<"insert "<<t3<<'\n'<<"quck "<<t4;
	return 0;
}
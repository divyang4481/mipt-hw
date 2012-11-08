#include<iostream>
using namespace std;
void BubbleSort(int *m,int s)
{for(int i=0;i<s;++i)
	for(int j=i+1;j<s;++j)
		if (m[j]<m[i]){
			int k;k=m[i];m[i]=m[j];m[j]=k;}
}
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
void msort(int *a,int n)
{
	int *c;
	c=new int[n];
    mergesort(a,0,n-1,c);
	delete[] c;
}
void insertsort(int *a,int n)
{
	for(int i=1;i<n;++i)
		for(int j=i-1;(j>-1)&&(a[j+1]<a[j]);--j)
		swap(a[j],a[j+1]);
}
void quicksort(int *a,int b,int e)
{
	int m=a[(b+e)/2];
	int b1=b,e1=e;
	do
	{
		while(a[b1]<m)++b1;
		while(a[e1]>m)--e1;
		if(e1>=b1){swap(a[e1],a[b1]);++b1;--e1;}
	}
	while(e1>b1);
	if(e1>b)quicksort(a,b,e1);
	if(b1<e)quicksort(a,b1,e);
}
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
void Heap(int *a,int k,int n)
{int max=a[k],m1=a[k]-1,m2=a[k]-1;
if ((2*(k+1)<n)&&(a[2*(k+1)]>max)){m1=a[2*(k+1)];max=m1;}
if ((2*(k+1)-1<n)&&(a[2*(k+1)-1]>max)){m2=a[2*(k+1)-1];max=m2;}
if (max==m1){swap(a[2*(k+1)],a[k]);Heap(a,2*(k+1),n);}else
	if(max==m2){swap(a[2*(k+1)-1],a[k]);Heap(a,2*(k+1)-1,n);}
}
void Heapstruct(int *a,int n)
{int m=(n-2)/2;
if (n-1<m)m=n-1;
	for(int i=m;i>=0;--i)Heap(a,i,n);
}
void Heapsort(int *a,int n)
{Heapstruct(a,n);
    swap(a[0],a[n-1]);
	for(int i=n-2;i>0;--i){
		Heap(a,0,i+1);swap(a[0],a[i]);}
}
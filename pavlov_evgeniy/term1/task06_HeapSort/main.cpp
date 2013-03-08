#include<iostream>
using namespace std;
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
int main()
{ int *a,n;
cin>>n;
a=new int[n];
for(int i=0;i<n;++i)cin>>a[i];
Heapsort(a,n);
for(int i=0;i<n;++i)cout<<a[i]<<' ';
delete[] a;
	return 0;
}

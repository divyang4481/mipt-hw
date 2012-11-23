#include <iostream>
using namespace std;

void Merge(int *a, int l, int m, int r, int *c)
{
	int i=l, j=m+1;
	int k=0;
	while (k<=r)
		if ((j>r) || (i<=m && a[i]<a[j]))
			c[k++]=a[i++];
		else
			c[k++] = a[j++];
	for (i=l, k=0; i<=r; ++i, ++k) a[i]=c[k];
}

void MergeSort(int *a, int l, int r, int *c)
{
	int m;
	if (r-l<1) {}
	else 
	{
		if (r-l==1)
		{
			if (a[l]>a[r]) swap(a[l],a[r]);
		}
		else 
		{
			m=(l+r)/2;
			MergeSort(a,l,m,c);
			MergeSort(a,m+1,r,c);
			Merge(a,l,m,r,c);
		}
	}
}

void MERGESORT(int *a, int n)
{
    int *c= new int[n];
    MergeSort(a,0,n-1,c);
	delete [] c;
}

int main()
{
	int n;
	scanf("%d",&n);
	int *a = new int[n];
	for (int i=0; i<n; ++i) scanf("%d",(a+i));
	MERGESORT(a,n);
	for (int i=0; i<n; ++i) printf("%d ",*(a+i));
	delete [] a;
	return 0;
}
// MERGE.cpp: определяет точку входа для консольного приложения.
//
#include <cstdio>
#include "stdafx.h"


void ArrayInTwo(int *a, int n, int *a1, int *a2)
{
	for (int i=0; i<n/2; i++)
	{
		a1[i]=a[i];
		a2[i]=a[i+n/2];
	}
	if (n%2==1) a2[n/2]=a[n-1];
}
void Merge(int *a1, int n1, int *a2, int n2, int *a)
{
	int i=0,j=0;
	while (i<n1 || j<n2)
	{
		if (i==n2)
		{
			a[i+j]=a2[j];
			j++;
			continue;
		}
		if (j==n2)
		{
			a[i+j]=a1[i];
			i++;
			continue;
		}
		if (a1[i]<a2[j])
		{
			a[i+j]=a1[i];
			i++;
		}
		else
		{
			a[i+j]=a2[j];
			j++;
		}
	}
}
void MergeSort(int *a,int n)
{
	if (n>1)
	{
		
		int *a1=new int [1000000];
		int *a2=new int [1000000];
		ArrayInTwo(a,n,a1,a2);
		MergeSort(a1,n/2);
		MergeSort(a2,n/2+n%2);
		Merge(a1, n/2, a2, n/2+n%2, a);
		delete [] a1;
		delete [] a2;
	}
}
int main()
{
	
	int *a=new int [1000000];
	int n;
	scanf("%d",&n);
	for (int i=0; i<n; i++) scanf("%d",&a[i]);
	MergeSort(a,n);
	for (int i=0; i<n; i++) printf("%d ",a[i]);
	delete [] a;
	return 0;
}



#include <stdio.h>

void swap(int &a, int &b) 
{ 
	int t = a; 
	a = b; 
	b = t; 
} 

void InsertSort(int *a, int n)
{
	for (int i = 1; i < n; ++i) 
	{
        int t = a[i];
		int j=i-1;
		while ((j>=0) && (a[j]>t))
		{
                a[j+1] = a[j];
                a[j]= t;
				j-=1;
        }
 
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	int *a= new int[n];
	for (int i=0; i<n; ++i) scanf("%d",(a+i));
	InsertSort(a, n);
	for (int i=0; i<n; ++i) printf("%d ",*(a+i));
	delete [] a;
	return 0;
}
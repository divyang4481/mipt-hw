#include <stdio.h>

void swap(int &a, int &b) 
{ 
	int t = a; 
	a = b; 
	b = t; 
} 

void qsort(int* a, int l, int r)
{
    int i = l, j = r, x = a[(l + r) / 2];
	while (i <= j)
    {
        while (a[i] < x) i++;
        while (a[j] > x) j--;
 
        if (i <= j) 
		{
            swap(a[i], a[j]);
            i++; j--;
        }
    } 
	
	if (l < j) qsort(a, l, j); 
    if (i < r) qsort(a, i, r);

}

 int main()
 {
	 int n;
	 scanf("%d", &n);
	 int *a= new int [n];
	 for (int i=0; i<n; ++i) scanf("%d", (a+i));
	 qsort(a, 0, n-1);
	 for (int i=0; i<n; ++i) printf("%d ", *(a+i));
	 delete [] a;
	 return 0;
 }
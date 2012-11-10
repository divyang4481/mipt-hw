#include <iostream>
using namespace std;

int ksearch(int* a, int l, int r, int k)
{
    int i = l, j = r, x = a[( rand()%(r-l+1) ) + l];
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
	
    if ((l<=k) && (k<=j)) ksearch(a, l, j, k);
    if ((i<=k) && (k<=r)) ksearch(a, i, r, k);
    return a[k];
}

 int main()
 {
	 int n, k;
	 scanf("%d %d", &n, &k);
	 int *a = new int [n];
	 for (int i=0; i<n; ++i) scanf("%d", (a+i));
	 printf("%d", ksearch(a, 0, n-1, k));
	 delete [] a;
	 return 0;
 }
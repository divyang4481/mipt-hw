#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

void CountSort(int *a, int k, int n)
{   
	if (n!=0)
	{
        int *temp = new int[n];
		int count[2];
		count[0] = 0; count[1] = 0;
		for (int i=0; i<n; ++i) ++count[(a[i] & (1<<k))>>k];
		count[1]+=count[0];
	    for (int i=n-1; i>=0; --i)
	    {
	        temp[count[(a[i] & (1<<k))>>k]-1] = a[i];
	        --count[(a[i] & (1<<k))>>k];
	    }
        for (int i = 0; i < n; ++i) a[i] = temp[i];
        delete [] temp;
	}
}

void RadixSort(int *a, int n)
{
	int MAX = abs(a[0]), d = 0;
	int n1 = 0, n2 = 0;
	for (int i=0; i<n; ++i) if (abs(a[i])>MAX) MAX=abs(a[i]);
	while (MAX) {MAX/=2; ++d;}
    int* b = new int[n];
    int* c = new int[n];
    for (int i = 0; i < n; ++i)
    {
        if (a[i] >= 0) b[n1++] = a[i];
        else c[n2++] = - a[i];		

    }
	for (int i=0; i<d; ++i) 
    {
        CountSort(c,i,n2);
        CountSort(b,i,n1);
    }
    if (n2) for (int i=0; i<n2; ++i)
    {
        a[n2-i-1]=-c[i];
    }
    if (n1) for (int i=0; i+n2<n; ++i)
    {
        a[i+n2]=b[i];
    }    
    delete [] b;
    delete [] c;
}

int main()
{
    int n;
	scanf("%d",&n);
	int *a = new int[n];
	for (int i=0; i<n; ++i) scanf("%d",(a+i));
	RadixSort(a, n);
    for (int i=0; i<n; ++i) printf("%d ",*(a+i));
	delete [] a;
	return 0;
}

#include <stdio.h>

void swap(int &a, int &b)
{
     int c=a;
     a=b;
     b=c;
}

void sort(int *a, int N)
{
     for (int i=0; i<N-1; ++i) 
     {
         for (int j=N-2; j>=i; --j)
         {
             if (a[j]>a[j+1]) {swap(a[j],a[j+1]);}
         }
     }  
}

int main()
{
    int n;
	scanf("%d",&n);
	int *a= new int[n];
    for (int i=0; i<n; ++i) scanf("%d",(a+i));
    sort(a,n);
    for (int i=0; i<n; ++i) printf("%d ",*(a+i));
	delete [] a;
    return 0;
}
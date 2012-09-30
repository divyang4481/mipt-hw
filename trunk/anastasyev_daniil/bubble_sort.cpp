#include <stdio.h>

const int N=10;

void swap(int *a, int *b)
{
     int c=*a;
     *a=*b;
     *b=c;
}

void sort(int a[], int N)
{
     for (int i=0; i<N-1; ++i) 
     {
         for (int j=N-2; j>=i; --j)
         {
             if (a[j]>a[j+1]) {swap(&a[j],&a[j+1]);}
         }
     }  
}

int main()
{
    int a[N];
    for (int i=0; i<N; ++i) {scanf("%d",&a[i]);}
    sort(a,N);
    for (int i=0; i<N; ++i) {printf("%d ",a[i]);}
    return 0;
}

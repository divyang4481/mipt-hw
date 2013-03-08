#include <cstdio>
#include <iostream>
using namespace std;
void Merge(int n, int k, int *a)
{
        int i=n, j=(n+k)/2+1, *b=new int[k-n+1];
        for (int h=n; h<=k; h++)
        {
                if (i>(n+k)/2)
                {
                        b[h]=a[j];
                        j++;
                        continue;
                }
                if (j>k)
                {
                        b[h]=a[i];
                        i++;
                        continue;
                }
                if (a[i]<a[j])
                {
                        b[h]=a[i];
                        i++;
                }
                else
                {
                        b[h]=a[j];
                        j++;
                }
        }
        for (int i=n; i<=k; i++) a[i]=b[i];
}
void MergeSort(int n, int k, int *a)
{
        if (k>n)
        {
                MergeSort(n, (n+k)/2, a);
                MergeSort((n+k)/2+1, k, a);
                Merge(n, k, a);
        }
}
int main()
{
        int n;
        scanf("%d",&n);
        int *a = new int[n];
        for (int i=0; i<n; i++) scanf("%d",&a[i]);
        printf("\n");
        MergeSort(0,n-1,a);
        for (int i=0; i<n; i++) printf("%d ",a[i]);
        printf("\n");
        delete [] a;
        return 0;
}
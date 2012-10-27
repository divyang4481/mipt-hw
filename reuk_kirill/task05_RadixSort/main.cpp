#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int n;

void RadixSort(int* a, int x)
{
    int m = 0;
    for (int i = 0; i < x; ++i)
        if (a[i] > m)
            m = a[i];
    int e = 1;
    int* b = new int[10];
    int* c = new int[x];
    while ((m/e)%10 > 0)
    {
        for (int i = 0; i < 10; ++i)
            b[i] = 0;
        for (int i = 0; i < x; ++i)
            b[(a[i]/e)%10]++;

        for (int i = 1; i < 10; ++i)
            b[i] += b[i - 1];
        for (int i = x - 1; i >= 0; --i)
        {
            c[--b[(a[i]/e)%10]] = a[i];
            //b[(a[i]/e)%10]--;
        }
        for (int i = 0; i < x; ++i)
            a[i] = c[i];
        e = e * 10;

    }

}


int main()
{
    scanf("%d", &n);

    int* a = new int[n];

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &(a[i]));
    }

    RadixSort(a, n);

    for (int i = 0; i < n; ++i)
    {
        printf("%d ", a[i]);
    }

    delete[] a;
    return 0;
}

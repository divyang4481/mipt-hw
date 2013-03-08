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
    int e = 0;
    int* b = new int[10];
    int* c = new int[x];
    while ((m >> e) > 0)
    {
        for (int i = 0; i < 2; ++i)
            b[i] = 0;
        for (int i = 0; i < x; ++i)
            b[(a[i] >> e)%2]++;

        for (int i = 1; i < 2; ++i)
            b[i] += b[i - 1];
        for (int i = x - 1; i >= 0; --i)
        {
            c[--b[(a[i] >> e)%2]] = a[i];
        }
        for (int i = 0; i < x; ++i)
            a[i] = c[i];
        e++;
    }

    delete[] b;
    delete[] c;

}


int main()
{
    scanf("%d", &n);

    int* a = new int[n];
    int* b = new int[n];
    int num;
    int a_count = 0;
    int b_count = 0;

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &num);
        if (num < 0)
            b[b_count++] = num;
        else
            a[a_count++] = num;
    }

    RadixSort(a, a_count);
    RadixSort(b, b_count);

    for (int i = 0; i < b_count; ++i)
    {
        printf("%d ", b[i]);
    }
    for (int i = 0; i < a_count; ++i)
    {
        printf("%d ", a[i]);
    }

    delete[] a;
    return 0;
}

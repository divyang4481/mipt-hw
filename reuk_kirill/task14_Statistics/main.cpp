#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
int n;

int part(int *a, int l, int r)
{
    int x = a[l + (rand() % (r - l + 1))];
    int i = l - 1;
    int j = r + 1;
    while (1)
    {
        do
            --j;
        while((a[j] >= x) && (j > l));
        do
            ++i;
        while ((a[i] <= x) && (i < r));
        if (i < j)
            swap(a[i], a[j]);
        else
            return j;
    }
    return 0;
}

int Statistic(int *a, int l, int r, int k)
{
    if (l==r)
        return a[l];

    int q = part(a, l, r);
    int s = q - l + 1;
    if (k < s)
        return Statistic(a, l, q, k);
    else
        return Statistic(a, q + 1, r, k - s);
}

int main()
{
    scanf("%d", &n);
    int k;
    scanf("%d", &k);

    int *a = new int[n];
    for(int i = 0; i < n; ++i)
        scanf("%d", &a[i]);

    printf("%d", Statistic(a, 0, n - 1, k - 1));

    delete[] a;

    return 0;
}

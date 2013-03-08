#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int n;

void QuickSort(int x, int y, int *a)
{
    if (x >= y)
        return;

    int i = x;
    int j = y;


    int m = a[rand() % (y + x)];

    if (x >= y)
        return;

    do {
        while (a[i] < m)
            ++i;
        while (a[j] > m)
            --j;
        if (i <= j) {
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    while (i <= j);

    QuickSort(x, j, a);
    QuickSort(i, y, a);
}


int main()
{
    scanf("%d", &n);

    int* a = new int[n];

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &(a[i]));
    }

    QuickSort(0, n - 1, a);

    for (int i = 0; i < n; ++i)
    {
        printf("%d ", a[i]);
    }

    delete[] a;
    return 0;
}

#include <iostream>
#include <stdio.h>

using namespace std;

int n;

void swap(int &a, int &b)
{
    int k = a;
    a = b;
    b = k;
}

void InsertSort(int *a, int n)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            if (a[i] < a[j])
                swap(a[i], a[j]);
}

int main()
{
    scanf("%d", &n);

    int* a = new int[n];

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &(a[i]));
    }

    InsertSort(a, n);

    for (int i = 0; i < n; ++i)
    {
        printf("%d ", a[i]);
    }

    delete[] a;

    return 0;
}

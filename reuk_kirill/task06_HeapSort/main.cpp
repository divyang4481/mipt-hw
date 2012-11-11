#include <iostream>
#include <stdio.h>

using namespace std;
int n;

void heapify(int *a, int num, int size)
{
    if (num*2 > size)
        return;
    int max_ind;
    if (num*2 < size)
    {
    if (a[num*2] < a[num*2 + 1])
        max_ind = num*2;
    else
        max_ind = num*2 + 1;
    }
    else
        max_ind = num*2;


    if (a[num] > a[max_ind])
        swap(a[num], a[max_ind]);

    heapify(a, max_ind, size);
}

int main()
{

    scanf("%d", &n);
    int* a = new int[n];
    int* res = new int[n];

    for (int i = 1; i<=n; ++i)
    {
        scanf("%d", &a[i]);
    }

    for (int i = (n/2); i>0; --i)
    {
        heapify(a, i, n);
    }

    int count = 0;
    for (int i = n; i>0; --i)
    {
        res[count++] = a[1];
        swap(a[1], a[i]);
        heapify(a, 1, i - 1);
    }

    for (int i = 0; i<n; ++i)
    {
        printf("%d ", res[i]);
    }

    delete[] a;
    delete[] res;
    return 0;
}

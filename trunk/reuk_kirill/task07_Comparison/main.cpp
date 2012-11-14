#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
int n;

bool check(int* a)
{
    for (int i = 1; i < n; ++i)
        if (a[i - 1] > a[i])
            return 0;
    return 1;
}

int* BubbleSort(int* a, int n)
{
    int t = clock();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < (n - 1); ++j)
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
    printf("BubbleSort time=%f ", ((float)(clock() - t)/CLOCKS_PER_SEC));
    return a;
}

int* MSort(int x, int y, int *a, int *b)
{
    int i;
    if ((y - x) > 1) {
    MSort(x, (x + y) / 2, a, b);
    MSort((x + y)/2 + 1, y, a, b);
    }

    int l = x, r = ((x + y) / 2 + 1), count = x;

    while (l <= ((x + y)/2) && (r <= y))
    {
        if (a[l] <= a[r])
            {
                b[count] = a[l];
                count++;
                l++;
            }
        else
            {
                b[count] = a[r];
                count++;
                r++;
            }
    }

    for (i = l; i <= ((x + y)/2); ++i)
    {
        b[count] = a[i];
        count++;
    }
    for (i = r; i <= y; ++i)
    {
        b[count] = a[i];
        count++;
    }

    for (int i = x; i <= y; ++i)
        {
            a[i] = b[i];
        }
    return a;
}

int* MergeSort(int x, int y, int *a)
{
    int t = clock();
    int* b = new int[n];
    MSort(x, y, a, b);
    printf("MergeSort time=%f ", ((float)(clock() - t)/CLOCKS_PER_SEC));
    return a;
}

int* InsertSort(int *a, int n)
{
    int t = clock();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            if (a[i] < a[j])
                swap(a[i], a[j]);
    printf("InsertSort time=%f ", ((float)(clock() - t)/CLOCKS_PER_SEC));
    return a;
}

int* QSort(int x, int y, int *a)
{
    if (x >= y)
        return a;

    int i = x;
    int j = y;

    int m = a[rand() % (y - x) + x];

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

    QSort(x, j, a);
    QSort(i, y, a);

    return a;
}

int* QuickSort(int x, int y, int *a)
{
    int t = clock();
    QSort(x, y, a);


    printf("Qucksort time=%f ", ((float)(clock() - t)/CLOCKS_PER_SEC));
    return a;
}


int* RSort(int* a, int x)
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

    return a;
}

int* RadixSort(int* arr, int n)
{
    int t = clock();
    int* a = new int[n];
    int* b = new int[n];
    int a_count = 0;
    int b_count = 0;

    for (int i = 0; i < n; ++i)
    {
        if (arr[i] < 0)
            b[b_count++] = arr[i];
        else
            a[a_count++] = arr[i];
    }

    RSort(a, a_count);
    RSort(b, b_count);
    for (int i = 0; i < b_count; ++i)
        arr[i] = b[i];
    for (int i = a_count; i < (a_count + b_count); ++i)
        arr[i] = a[i - b_count];

    printf("Radixsort time=%f ", ((float)(clock() - t)/CLOCKS_PER_SEC));
    return a;
}

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

int* HeapSort(int* a, int n)
{
    int t = clock();
    int* res = new int[n];

    for (int i = (n/2); i>0; --i)
        heapify(a, i, n);

    int count = 0;
    for (int i = n; i>0; --i)
    {
        res[count++] = a[1];
        swap(a[1], a[i]);
        heapify(a, 1, i - 1);
    }
    printf("HeapSort time=%f ", ((float)(clock() - t)/CLOCKS_PER_SEC));

    return res;
}

int* generate()
{
    int* a = new int[n];
    for (int i = 0; i<n; ++i)
        a[i] = rand();
    return a;
}

int main()
{
    scanf("%d", &n);

    if (n < 30000)
    {
        printf("correct=%d\n", check(BubbleSort(generate(), n)));

        printf("correct=%d\n", check(InsertSort(generate(), n)));
    }

    printf("correct=%d\n", check(MergeSort(0, n - 1, generate())));

    printf("correct=%d\n", check(QuickSort(0, n - 1, generate())));

    printf("correct=%d\n", check(RadixSort(generate(), n)));

    printf("correct=%d\n", check(HeapSort(generate(), n)));

    return 0;
}

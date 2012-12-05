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
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < (n - 1); ++j)
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
    return a;
}

int* MergeSort(int x, int y, int *a, int *b)
{
    int i;
    if ((y - x) > 1) {
    MergeSort(x, (x + y) / 2, a, b);
    MergeSort((x + y)/2 + 1, y, a, b);
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

int* InsertSort(int *a, int n)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            if (a[i] < a[j])
                swap(a[i], a[j]);
    return a;
}

int* QuickSort(int x, int y, int *a)
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

    QuickSort(x, j, a);
    QuickSort(i, y, a);

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
    return res;
}

void PrintName(int i)
{
    switch (i) {
	case 1:
		printf("BubbleSort ");
		break;
	case 2:
		printf("InsertSort ");
		break;
	case 3:
		printf("MergeSort ");
		break;
	case 4:
		printf("QuickSort ");
		break;
	case 5:
		printf("RadixSort ");
		break;
	case 6:
		printf("HeapSort ");
		break;
	}
}

int* Sorting(int* a, int n, int i)
{
    switch (i) {
	case 1:
        return BubbleSort(a, n);
	case 2:
		return InsertSort(a, n);
	case 3:
	{
        int *b = new int[n];
        a = MergeSort(0, n-1, a, b);
		delete[] b;
		return a;
	}
	case 4:
		return QuickSort(0, n-1, a);
	case 5:
		return RadixSort(a, n);
	case 6:
		return HeapSort(a, n);
    }
    return 0;
}

int main()
{
    scanf("%d", &n);

    int *a = new int[n];

    int i;
    if (n < 30000)
        i = 1;
    else
        i = 3;
    for (; i < 7; ++i)
    {
        for (int j = 0; j<n; ++j)
            a[j] = rand();

        float t = clock();

        a = Sorting(a, n, i);

        float ct = clock() - t;
        PrintName(i);
        printf("Correct=%d; Time=%fms \n", check(a), (float)(ct/CLOCKS_PER_SEC));
    }

    /*if (n < 30000)
    {
        printf("correct=%d\n", check(BubbleSort(generate(), n)));

        printf("correct=%d\n", check(InsertSort(generate(), n)));
    }

    printf("correct=%d\n", check(MergeSort(0, n - 1, generate())));

    printf("correct=%d\n", check(QuickSort(0, n - 1, generate())));

    printf("correct=%d\n", check(RadixSort(generate(), n)));

    printf("correct=%d\n", check(HeapSort(generate(), n)));*/

    delete[] a;
    return 0;
}

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;

using namespace std;

float KahanSum(float* a, int n)
{
    float sum = 0;
    float comp = 0;
    for (int i = 1; i <= n; ++i)
    {
        float y = a[i] - comp;
        float t = sum + y;
        comp = (t - sum) - y;
        sum = t;
    }
    return sum;
}

void heapify(float *a, int num, int size)
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

void MakeHeap(float *a, int n)
{
    for (int i = (n/2); i>0; --i)
    {
        heapify(a, i, n);
    }
}

float CompSum(float *a, int n)
{
    MakeHeap(a, n);

    for (int i = n; i>1; --i)
    {
        float sum = a[1];
        swap(a[1], a[i]);
        heapify(a, 1, i - 1);
        sum += a[1];
        a[1] = sum;
        heapify(a, 1, i - 1);
    }
    return a[1];
}
int main()
{
    cin >> n;
    float* a = new float[n];
    for (int i = 1; i<=n; ++i)
    {
        cin >> a[i];
    }
    cout << KahanSum(a, n) << endl;
    cout << CompSum(a, n) << endl;
    return 0;
}

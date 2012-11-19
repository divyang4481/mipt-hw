#include <iostream>

using namespace std;

int CountingSort(int* a, int k, int len, int t)
{
    int* b = new int [len];
    int* c = new int[k];
    for (int i = 0; i < k; ++i)
        c[i] = 0;
    for (int i = 0; i < len; ++i)
        ++c[(a[i] / t) % 10];
    for (int i = 1; i < k; ++i)
        c[i] += c[i-1];
    for (int i = len-1; i >= 0; --i)
    {
        b[c[(a[i] / t) % 10]-1] = a[i];
        --c[(a[i] / t) % 10];
    }
    for (int i = 0; i < len; ++i)
        a[i] = b[i];
    delete[] b;
    delete[] c;
    return 0;
}

int RadixSort(int* a, int len)
{
    int d = 0;
    int max = abs(a[0]);
    for (int i = 0; i < len; ++i)
        if (abs(a[i]) > max)
            max = abs(a[i]);
    for (int i = 1; i < max; i *= 10, ++d);
    int count = 0;
    for (int i = 0; i < len; ++i)
        if (a[i] >= 0)
            ++count;
    int* pos = new int[count];
    int* neg = new int[len - count];
    for (int i = 0, p = 0, n = 0; i < len; ++i)
    {
        if (a[i] >= 0)
        {
            pos[p] = a[i];
            ++p;
        }
        else
        {
            neg[n] = - a[i];
            ++n;
        }
    }
    int t = 1;
    for (int i = 0; i < d; ++i, t *= 10)
    {
        CountingSort(pos, 10, count, t);
        CountingSort(neg, 10, len - count, t);
    }
    for (int i = len - count - 1; i >= 0 ; --i)
        a[i] = - neg[len - count - i - 1];
    for (int i = len - count; i < len; ++i)
        a[i] = pos[i - len + count];
    delete[] pos;
    delete[] neg;
    return 0;
}

int main()
{
    int N = 0;
    cin >> N;
    int* A = new int[N];
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    RadixSort(A, N);
    for (int i = 0; i < N; ++i)
        cout << A[i] << endl;
    delete[] A;
    return 0;
}
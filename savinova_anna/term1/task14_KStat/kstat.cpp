#include <iostream>
using namespace std;

int KSearch(int* a, int b, int f, int K)
{
    int k = --K;
    if (b < f)
    {
        int l = b, r = f;
        int x = a[(rand() % (r - l + 1)) + l];
        while (l <= r)
        {
            while (a[l] < x) ++l;
            while (a[r] > x) --r;
            if (l <= r)
            {                
                    int tmp = a[l];
                    a[l] = a[r];
                    a[r] = tmp;                
                    ++l;
                    --r;
            }
        }
        if ((b <= k) && (k <= r)) 
            KSearch(a, b, r, k);
        if ((l <= k) && (k <= f)) 
            KSearch(a, l, f, k);
        return a[k];
    }
}
int main()
{
    int N = 0;
    cin >> N;
    int* A = new int[N];
    int k = 0;
    cin >> k;
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    int X = KSearch(A, 0, N-1, k);
    cout << X;
    return 0;
}
#include <iostream>

using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    int* A = new int[n + 1];
    int* B = new int[n + 1];
    A[0]=1;
    A[1]=1;
    for (int i = 0; i <= n; ++i)
    {
       B[0] = 1;
       B[i] = 1;
       for (int j = 1; j < i; ++j)
       {
           B[j] = A[j-1] + A[j];
       }
       for (int j = 0; j <= i; ++j)
           A[j] = B[j];
    }
    for (int k = 0; k <= n; ++k)
        cout << A[k] << endl;
    return 0;
}

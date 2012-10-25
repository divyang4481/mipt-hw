#include "stdafx.h"
#include <iostream>

using namespace std;

int** CreateMatr(int h)
{
    
    int** buf = new int*[h];
    for (int i = 0; i < h; ++i)
    {
        *(buf + i)=new int[h];
    }
    return buf;
}

void DeleteMatr(int** buf, int h)
{
    for (int i = 0; i < h; ++i)
    {
        delete[] *(buf + i);
    }
    delete[] buf;
}
int main()
{
    int n = 0;
    cin >> n;
    int** A = CreateMatr(n+1);
    for (int i = 0; i <= n; ++i)
    {
       A[i][0] = 1;
       A[i][i] = 1;
       for(int j = 1;j < i; ++j)
       {
           A[i][j] = A[i-1][j-1] + A[i-1][j];
       }
    }
    for (int k = 0; k <= n; ++k)
        cout << A[n][k] << endl;
    DeleteMatr(A, n);
    return 0;
}
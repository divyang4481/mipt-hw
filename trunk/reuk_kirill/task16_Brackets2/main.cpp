#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    n *= 2;

    long long int** a;
    a = new long long int*[n+1];
    for (int i = 0; i <= n; ++i)
        a[i] = new long long int[n+1];

    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            a[i][j] = 0;

    a[1][1] = 1;

    for (int i = 2; i <= n; ++i)
    {
        a[i][0] = a[i-1][1];
        for (int j = 1; j <= n; ++j)
            a[i][j] = a[i-1][j-1] + a[i-1][j+1];
    }


    printf("%d", a[n][0]);

    for (int i = 0; i < n; ++i)
        delete[] a[i];
    delete[] a;

    return 0;
}

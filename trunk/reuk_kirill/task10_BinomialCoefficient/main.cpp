#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()
{
    long long n;
    scanf("%lld", &n);
    long long x = 1;
    for (int i = 0; i <= n; ++i)
    {
         printf("%lld\n", x);
         x *= n - i;
         x /= i + 1;
    }
    return 0;
}

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    if (n == 1)
    {
        printf("NO");
        return 0;
    }

    for (int i = sqrt(n); i > 2; --i)
        if ((n%i)==0)
        {
            printf("NO");
            return 0;
        }

    printf("YES");
    return 0;
}

#include <iostream>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

int n;

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}


int main()
{

    scanf("%d", &n);

    int* a = new int[n];

    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < (n - 1); ++j)
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }

    for (int i = 0; i < n; ++i)
        printf("%d ", a[i]);

    free(a);
    return 0;
}

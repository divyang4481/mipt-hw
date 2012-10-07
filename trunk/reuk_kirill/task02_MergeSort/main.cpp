#include <iostream>
#include <stdio.h>

using namespace std;

int n;

void MergeSort(int x, int y)
{
    int i;
    if ((y - x) > 1) {
    merge(x, (x + y) / 2);
    merge((x + y)/2 + 1, y);
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
}

int main()
{
    scanf("%d", &n);

    int* a = new int[n];
    int* b = new int[n];


    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &(a[i]));
    }

    merge(0, n - 1);

    for (int i = 0; i < n; ++i)
    {
        printf("%d ", a[i]);
    }


    return 0;
}

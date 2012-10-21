#include "includes.h"

void QuickSort(int* a, int n) {
    int left = 1, right = n;
    int x = a[0];

    while (left < right) {
        if (a[left] <= x)
            ++left;
        else
            if (a[right - 1] > x)
                --right;
            else
                swap(a[left], a[right - 1]);
    }

    if (left == n) {
        --left;
        swap(a[0], a[left]);
    }

    if (n > 1) {
        QuickSort(a, left);
        QuickSort(a + right, n - right);
    }
}
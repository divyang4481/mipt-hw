#include "includes.h"

void InsertSort(int* a, int n) {
    for (int i = 1; i < n; ++i) {
        int j = i;
        while (j - 1 >= 0 && a[j - 1] > a[i])
            --j;
        int buffer = a[i];
        for (int k = i; k > j; --k)
            a[k] = a[k-1];
        a[j] = buffer;
    }
}
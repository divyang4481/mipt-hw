#include "includes.h"

#include <algorithm>
#include <vector>

const int base = 10;
typedef vector < vector <int> > table_t;

void RadixSortHelper(int *a, int size) {
    if (size <= 0)
        return;
    int pow = 1;
    int maxElement = *max_element(a, a + size);
    int sign = 1;
    if (a[0] < 0) {
        maxElement = *min_element(a, a + size);
        sign = -1;
    }
    while (sign * maxElement > 0) {
        table_t table (base);
        for (int i = 0; i < size; ++i)
            table[abs(a[i]) / pow % base].push_back(a[i]);

        int current_size = 0;
        for (int row = 0; row < base; ++row)
            for (int pos = 0; pos < (int) table[row].size(); ++pos)
                a[current_size++] = table[row][pos];
        pow *= base;
        maxElement /= base;
    }
}

void RadixSort(int *a, int size) {
    int *positive = (int*) malloc(size * sizeof(int));
    int *negative = (int*) malloc(size * sizeof(int));
    int posCount = 0;
    int negCount = 0;
    for (int i = 0; i < size; ++i)
        if (a[i] >= 0)
            positive[posCount++] = a[i];
        else
            negative[negCount++] = a[i];
    RadixSortHelper(positive, posCount);
    RadixSortHelper(negative, negCount);
    for (int i = 0; i < negCount; ++i)
        a[i] = negative[negCount - 1 - i];
    for (int i = 0; i < posCount; ++i)
        a[i + negCount] = positive[i];

    free(negative);
    free(positive);
}
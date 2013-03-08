#include "includes.h"

void MergeSortHelper(int* a, int size, int* pBuffer) {
    if (size <= 1)
        return;
    int n = size / 2;
    int m = size - n;
    for (int i = 0; i < n; ++i)
        pBuffer[i] = a[i];
    for (int j = n; j < n + m; ++j)
        pBuffer[j] = a[j];

    MergeSortHelper(pBuffer, n, pBuffer + size);
    MergeSortHelper(pBuffer + n, m, pBuffer + size);

    int i = 0;
    int j = 0;
    for (int k = 0; k < size; ++k) {
        if (i < n) {
            if (j < m) {
                if (pBuffer[i] < pBuffer[n + j])
                    a[k] = pBuffer[i++];
                else
                    a[k] = pBuffer[n + j++];
            }
            else
                a[k] = pBuffer[i++];
        }
        else
            a[k] = pBuffer[n + j++];
    }
}

void MergeSort(int *a, int size) {
    int* pBuffer = (int*) malloc((size_t) 2 * 1.1 * size * sizeof(int));      //  as Limit[Sigma[1/(2^x), {x, 0, N}], N->Infinity] = 2
    assert(pBuffer != NULL);
    MergeSortHelper(a, size, pBuffer);
    free(pBuffer);
}
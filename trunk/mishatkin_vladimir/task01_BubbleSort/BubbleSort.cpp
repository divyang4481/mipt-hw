#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <iostream>

using namespace std;

void BubbleSort(int* a, int size) {
    bool swapped = true;
    int* pBuffer = (int*) malloc(1 * sizeof(int));
    assert(pBuffer != NULL);
    for (int i = 0; i < size && swapped; ++i) {
        swapped = false;
        for (int j = 0; j < size - 1 - i; ++j)
            if (a[j] > a[j + 1]) {
                *pBuffer = a[j];
                a[j] = a[j + 1];
                a[j + 1] = *pBuffer;
                swapped = true;
            }
    }
    free(pBuffer);
}

int main() {
    int N;
    scanf("%d\n", &N);
    int* a = new int[N];
    for (int i = 0; i < N; ++i)
        scanf("%d", &a[i]);

    BubbleSort(a, N);
    for (int i = 0; i < N; ++i) {
        if (i)
            printf(" ");
        printf("%d", a[i]);
    }
    printf("\n");
    return 0;
}
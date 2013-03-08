#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <iostream>

using namespace std;

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

int main() {
    int N;
    scanf("%d\n", &N);
    int* a = (int*) malloc((size_t) N * sizeof(int));
    assert(a != NULL);
    for (int i = 0; i < N; ++i)
        scanf("%d", &a[i]);

    InsertSort(a, N);
    for (int i = 0; i < N; ++i) {
        if (i)
            printf(" ");
        printf("%d", a[i]);
    }
    printf("\n");
    free(a);
    return 0;
}
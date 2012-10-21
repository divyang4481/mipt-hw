#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <iostream>

using namespace std;

void QuickSort(int a[], int n) {
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

int main() {
    int N;
    scanf("%d\n", &N);
    int* a = (int*) malloc((size_t) N * sizeof(int));
    assert(a != NULL);
    for (int i = 0; i < N; ++i)
        scanf("%d", &a[i]);

    QuickSort(a, N);
    for (int i = 0; i < N; ++i) {
        if (i)
            printf(" ");
        printf("%d", a[i]);
    }
    printf("\n");
    free(a);
    return 0;
}
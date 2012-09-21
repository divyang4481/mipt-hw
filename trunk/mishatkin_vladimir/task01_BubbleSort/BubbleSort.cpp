#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <iostream>

using namespace std;

void BubbleSort(int* a, int size) {
    bool swapped = true;
    for (int i = 0; i < size && swapped; ++i) {
        swapped = false;
        for (int j = 0; j < size - 1 - i; ++j)
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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
    delete a;
    return 0;
}
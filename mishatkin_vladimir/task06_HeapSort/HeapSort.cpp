#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <iostream>

using namespace std;

void retainHeapAt(int* heap, int size, int id) {
    assert(id < size);
    int leftChild;
    int rightChild;
    int largestChild;
    while (true) {
        leftChild = 2 * id + 1;
        rightChild = 2 * id + 2;
        largestChild = id;
        if (leftChild < size && heap[leftChild] > heap[largestChild])
            largestChild = leftChild;
        if (rightChild < size && heap[rightChild] > heap[largestChild])
            largestChild = rightChild;

        if (largestChild == id)
            return;
        swap(heap[id], heap[largestChild]);
        id = largestChild;
    }
}

void make_heap(int* heap, int size) {
    for (int i = size / 2; i >= 0; --i)
        retainHeapAt(heap, size, i);
}

void heap_down(int* heap, int size, int id) {
    int child = 2 * id + 1;
    while (child < size) {
        if (child + 1 < size && heap[child + 1] > heap[child])
            ++child;
        if (heap[child] > heap[id]) {
            swap(heap[child], heap[id]);
            id = child;
        }
        child = 2 * child + 1;
    }
}

int heap_extract_max(int* heap, int &size) {
    swap(heap[0], heap[(size--) - 1]);
    heap_down(heap, size, 0);
    return heap[size];
}

void HeapSort(int* heap, int size) {
    make_heap(heap, size);
    while (size > 0)
        heap_extract_max(heap, size);
}

int main() {
    int N;
    scanf("%d\n", &N);
    int* a = (int*) malloc((size_t) N * sizeof(int));
    assert(a != NULL);
    for (int i = 0; i < N; ++i)
        scanf("%d", &a[i]);

    HeapSort(a, N);
    for (int i = 0; i < N; ++i) {
        if (i)
            printf(" ");
        printf("%d", a[i]);
    }
    printf("\n");
    free(a);
    return 0;
}
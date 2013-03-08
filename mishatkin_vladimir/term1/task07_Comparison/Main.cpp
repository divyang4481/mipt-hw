#include "includes.h"

#include <time.h>
#include <vector>
#include <string>

const int maxRandomValue = (int) 1e9;

void MergeSort(int*, int);
void InsertSort(int*, int);
void QuickSort(int*, int);
void RadixSort(int*, int);
void HeapSort(int*, int);

typedef int (*Functor)();
typedef void (*SortingFunctor)(int*, int);

typedef struct {
    string name;
    SortingFunctor sortingMethod;
} Sort;

Sort createSortStruct(string name, SortingFunctor sortingMethod) {
    Sort temp;
    temp.name = name;
    temp.sortingMethod = sortingMethod;
    return temp;
}

void initSorts(vector<Sort> &sorts) {
    sorts.resize(5);
    sorts[0] = createSortStruct("MergeSort", MergeSort);
    sorts[1] = createSortStruct("QuickSort", QuickSort);
    sorts[2] = createSortStruct("HeapSort", HeapSort);
    sorts[3] = createSortStruct("RadixSort", RadixSort);
    sorts[4] = createSortStruct("InsertSort", InsertSort);
}

int generateRandomNumber() {
    return ((rand() & 1) ? 1 : -1) * (rand() * rand() % (maxRandomValue + 1));
}

void generateArrayBySize(int *a, int n, Functor generator) {
    for (int i = 0; i < n; ++i)
        a[i] = generator();
}

void copyArray(int *source, int n, int *dest) {
    for (int i = 0; i < n; ++i)
        dest[i] = source[i];
}

bool isSorted(int *a, int n) {
    bool nonDecreasingOrder = true;
    for (int i = 1; i < n && nonDecreasingOrder; ++i)
        nonDecreasingOrder &= (a[i-1] <= a[i]);
    return nonDecreasingOrder;
}

int main() {
    vector<Sort> sorts;
    initSorts(sorts);

    int N;
    cin >> N;
    int *a = (int*) malloc((size_t) N * sizeof(int));
    assert(a != NULL);

    srand(time(NULL));
    Functor defaultGenerator = generateRandomNumber;
    generateArrayBySize(a, N, defaultGenerator);
   
    int *toSort = (int*) malloc((size_t) N * sizeof(int));
    assert(toSort != NULL);

    int size = (int) sorts.size();
    for (int testCase = 0; testCase < size-1; ++testCase) {
        copyArray(a, N, toSort);
        clock_t begin = clock();
        sorts[testCase].sortingMethod(toSort, N);
        clock_t workTime = clock() - begin;
//      <НазваниеАлгоритма> <время работы алгоритма в мс> <корректность работы (true/false)>
        cout << sorts[testCase].name << " " << workTime << " " << (isSorted(toSort, N) ? "true" : "false") << "\n";
    }
    free(toSort);
    
    free(a);
    return 0;
}
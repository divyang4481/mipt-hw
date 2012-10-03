//Merge Sort

#include <cstdio>
#include <cstdlib>
 
void merge(int left, int mid, int right, int* array){
    int i1 = 0;
    int i2 = left;
    int i3 = mid + 1;
 
    int *temp = (int*) malloc((right - left + 1)*sizeof(int));
 
    while ((i2 <= mid) && (i3 <= right)){
        if (*(array + i2) < *(array + i3))
            *(temp + i1++) = *(array + i2++);
        else
            *(temp + i1++) = *(array + i3++);
    }
    while (i2 <= mid)
        *(temp + i1++) = *(array + i2++);
    while (i3 <= right)
        *(temp + i1++) = *(array + i3++);
 
    for(int i = left; i <= right; ++i)
        *(array + i) = *(temp + i - left);
 
}
 
void MergeSort(int left, int right, int *array){
    if (left < right){
        int mid = (left + right) / 2;
        MergeSort(left, mid, array);
        MergeSort(mid + 1, right, array);
        merge(left, mid, right, array);
    }
}
 
int main()
{
        int N;
 
		scanf("%d", &N);
        int *array = (int*) malloc(N*sizeof(int));
        for (int i = 0; i < N; i++)
            scanf("%d", &(*(array+i)));
 
        MergeSort(0, N - 1, array);
 
        for (int i = 0; i < N; i++)
            printf("%d ", *(array+i));
		
		delete[] array;

        return 0;
}
 
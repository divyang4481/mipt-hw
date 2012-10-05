//Merge Sort

#include <cstdio>
#include <cstdlib>
 
void merge(int left, int mid, int right, int *a, int *temp){
    int i1 = 0;
    int i2 = left;
    int i3 = mid + 1;
 
    while ((i2 <= mid) && (i3 <= right)){
        if (a[i2] < a[i3])
            temp[i1++] = a[i2++];
        else
            temp[i1++] = a[i3++];
    }
    while (i2 <= mid)
        temp[i1++] = a[i2++];
    while (i3 <= right)
        temp[i1++] = a[i3++];
 
    for(int i = left; i <= right; ++i)
        a[i] = temp[i - left];
 
}
 
void MergeSort(int left, int right, int *a, int *temp){
    if (left < right){
        int mid = (left + right) / 2;
        MergeSort(left, mid, a, temp);
        MergeSort(mid + 1, right, a, temp);
        merge(left, mid, right, a, temp);
    }
}
 
int main()
{
    int N;
 
    scanf("%d", &N);
    int *a = (int*) malloc(N*sizeof(int));
    int *temp = (int*) malloc((N + 1)*sizeof(int));

    for (int i = 0; i < N; i++)
        scanf("%d", &(a[i]));
 
    MergeSort(0, N - 1, a, temp);
 
    for (int i = 0; i < N; i++)
        printf("%d ", a[i]);
   
	free(a);
	free(temp);

    return 0;
}
 
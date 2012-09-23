//Merge Sort

#include <cstdio>
#define NMax 1000

int a[NMax];
int temp[NMax];

void merge(int left, int mid, int right){
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

void MergeSort(int left, int right){
    if (left < right){
        int mid = (left + right) / 2;
        MergeSort(left, mid);
        MergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

int main()
{
	int N, i;

	scanf("%d", &N);
	for (i = 0; i < N; i++)
		scanf("%d", &a[i]);

	MergeSort(0, N - 1);

	for (i = 0; i < N; i++)
		printf("%d ", a[i]);

	return 0;
}

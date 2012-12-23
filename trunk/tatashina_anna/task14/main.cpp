#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

void Q_stat(int left, int right, int *a, int k) {
		
    int m = a[left + rand() % (right - left + 1)];

	int i = left;
	int j = right;
	do {
		while (a[i] < m) 
			i++;
		while (a[j] > m)
			j--;
		if (i <= j) {
			swap(a[i], a[j]);
			i++;
			j--;
		}
	}while (i <= j);

	if (k < j) Q_stat(left, j, a, k);
	if (i < k) Q_stat(i, right, a, k);
	
}
	
int Kth_order_statistics(int N, int *a, int k) {
	Q_stat(0, N - 1, a, k);
	return a[k];
}

int main()
{
    int N;
    int k;
    scanf("%d", &N);
    scanf("%d", &k);
    int *a = (int*) malloc(N*sizeof(int));

    for (int i = 0; i < N; i++)
        scanf("%d", &(a[i]));
 
    printf("%d ", Kth_order_statistics(N, a, k));

    free(a);

    return 0;
}
//Bubble Sort

#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

void Bubble_sort(int N, int *a) {
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N - 1; ++j)
			if (a[j] > a[i])
				swap(a[i], a[j]);
}

int main()
{
	int N;
	scanf("%d", &N);
	int* a = (int*) malloc(N*sizeof(int));

	for (int i = 0; i < N; ++i)
		scanf("%d", &(a[i]));
        
	Bubble_sort(N, a);
    
	for (int i = 0; i < N; ++i)
		printf("%d ", a[i]);
    
	free(a);
        
	return 0;
 
}
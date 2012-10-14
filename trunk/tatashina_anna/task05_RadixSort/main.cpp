//Insert Sort

#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;


int findD(int *a, int N) {
	int D;
	int max;
	D = 0;
	max = a[0];
	for (int i = 0; i < N; i++) 
		if (a[i] > max) {
			max = a[i];
			
		}

	while (max)
	{
		D++;
		max /= 10;
	}


	return D;
}




	

void RadixSort(int *a, int N) {
	int D;
	D = findD(a, N);
    int *b = (int*) malloc(N*sizeof(int));	
	int c[10];
	int q = 1;

	for (int i = 0; i < D; i++) {
		for (int j = 0; j < 10; j++)
			c[j] = 0;

		for (int j = 0; j < N; j++)
			c[(a[j] / q) % 10]++;

		for (int j = 1; j < 10; j++)
			c[j] = c[j] + c[j - 1];

		for (int j = 0; j < 10; j++) 
			c[j]--;

		for (int j = N - 1; j >= 0; j--) {
			b[c[(a[j] / q) % 10]] = a[j];
			c[(a[j] / q) % 10]--;
		}
		for (int j = 0; j < N; j++) 
			a[j] = b[j];

		q *= 10;
	} 
}


 
int main()
{
    int N, D;
 
    scanf("%d", &N);
    int *a = (int*) malloc(N*sizeof(int));


    for (int i = 0; i < N; i++)
        scanf("%d", &(a[i]));
	
	RadixSort(a, N);

   for (int i = 0; i < N; i++)
       printf("%d ", a[i]);
   
	free(a);


    return 0;
}
 
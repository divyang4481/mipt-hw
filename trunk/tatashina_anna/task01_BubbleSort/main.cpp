//Таташина Анна, 296
//Bubble Sort

#include "stdafx.h"
#include <stdio.h>
#define NMax 1000

void swap (int &x, int &y){
   int z = x;
   x = y;
   y = z; 
}

int main()
{
	int N, i, j;
	int a[NMax];
	
	scanf("%d", &N);
	for (i = 0; i < N; ++i)
		scanf("%d", &a[i]);
	
	for (i = 0; i < N; ++i){
		for (j = 0; j < N - 1; ++j){
			if (a[j] > a[i]) {
				swap(a[i], a[j]);
			}
		}
	}

	for (i = 0; i < N; ++i)
		printf("%d ", a[i]);
		
return 0;

}


//Quick Sort 

#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int QSort_K(int left, int right, int *a, int k) {
        int m = a[rand()%(right - left + 1)];
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

		if (k <= j) QSort_K(left, j, a, k);
	    if (i <= k) QSort_K(i, right, a, k);
		return k;
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
 
    QSort_K(0, N - 1, a, k - 1);

    
    printf("%d ", a[k - 1]);
   
    free(a);

    return 0;
}

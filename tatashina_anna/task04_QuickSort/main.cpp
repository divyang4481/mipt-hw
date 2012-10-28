
//Quick Sort 

#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

void QSort(int left, int right, int *a) {
        int m = a[(left + right) / 2];
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
        if (left < j)
                QSort(left, j, a);
        if (i < right)
                QSort(i, right, a);
}
 
int main()
{
    int N;
 
    scanf("%d", &N);
    int *a = (int*) malloc(N*sizeof(int));

    for (int i = 0; i < N; i++)
        scanf("%d", &(a[i]));
 
        QSort(0, N - 1, a);

    for (int i = 0; i < N; i++)
        printf("%d ", a[i]);
   
        free(a);


    return 0;
}
 
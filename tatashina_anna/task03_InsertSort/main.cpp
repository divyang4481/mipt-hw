//Insert Sort

#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;


void InsertSort(int left, int right, int *a) {
        int buf;
        int j;
        for (int i = left; i < right; i++) {
                buf = a[i];
                for (j = i - 1; ((j >= 0) && (a[j] > buf)); j--) {
                        a[j + 1] = a[j];
                }
                a[j + 1] = buf;
        }
}
 
int main()
{
    int N;
 
    scanf("%d", &N);
    int *a = (int*) malloc(N*sizeof(int));

    for (int i = 0; i < N; i++)
        scanf("%d", &(a[i]));
 
        InsertSort(0, N, a);

    for (int i = 0; i < N; i++)
        printf("%d ", a[i]);
   
        free(a);


    return 0;
}
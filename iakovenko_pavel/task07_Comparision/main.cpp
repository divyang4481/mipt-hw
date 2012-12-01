#include <iostream>
#include "sorts.h"
#include <time.h>
#include <algorithm>
using namespace std;

bool IsCorrect (int* arr,int n){
	for (int i=1; i<n; ++i)
		if (arr[i-1]>arr[i]) return false;
	return true;
}
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main(){
	int n;
	cin >> n;
	clock_t t;
	int* arr=new int [n];
	for (int j=0; j<n; j++)
		arr[j]=rand()-RAND_MAX/2;
	t=clock();
	MergeSort(arr,0,n-1);
	t=clock()-t;
	printf("MergeSort	time:%Lf	correct:", ((double)t)/CLOCKS_PER_SEC);
	(IsCorrect(arr, n))? cout <<"true\n":cout <<"false\n";
	for (int j=0; j<n; j++)
		arr[j]=rand()-RAND_MAX/2;
	t=clock();
	InsertionSort(arr, n);
	t=clock()-t;
	printf("InsertSort	time:%Lf	correct:", ((double)t)/CLOCKS_PER_SEC);
	(IsCorrect(arr, n))? cout <<"true\n":cout <<"false\n";
	for (int j=0; j<n; j++)
		arr[j]=rand()-RAND_MAX/2;
	t=clock();
	QuickSort(arr,0,n-1);
	t=clock()-t;
	printf("QuickSort	time:%Lf	correct:", ((double)t)/CLOCKS_PER_SEC);
	(IsCorrect(arr, n))? cout <<"true\n":cout <<"false\n";
	for (int j=0; j<n; j++)
		arr[j]=rand()-RAND_MAX/2;
	t=clock();
	RadixSort(arr,n);
	t=clock()-t;
	printf("RadixSort	time:%Lf	correct:", ((double)t)/CLOCKS_PER_SEC);
	(IsCorrect(arr, n))? cout <<"true\n":cout <<"false\n";
	for (int j=0; j<n; j++)
		arr[j]=rand()-RAND_MAX/2;
	t=clock();
	HeapSort(arr,n);
	t=clock()-t;
	printf("HeapSort	time:%Lf	correct:", ((double)t)/CLOCKS_PER_SEC);
	(IsCorrect(arr, n))? cout <<"true\n":cout <<"false\n";
	for (int j=0; j<n; j++)
		arr[j]=rand()-RAND_MAX/2;
	t=clock();
	qsort(arr,n,sizeof(int),compare);
	t=clock()-t;
	printf("qsort		time:%Lf	correct:", ((double)t)/CLOCKS_PER_SEC);
	(IsCorrect(arr, n))? cout <<"true\n":cout <<"false\n";
	delete[] arr;
	system("pause");
	return 0;
}
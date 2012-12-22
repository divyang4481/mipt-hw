#include <iostream>
#include "functions.h"
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
	srand((unsigned int)time(0));
	int* arr=new int [n];
	int* temp=new int [n];
	for (int j=0; j<n; j++)
		arr[j]=rand()-RAND_MAX/2;
	for (int i=0; i<n; i++)
		temp[i]=arr[i];
	t=clock();
	MergeSort(temp,0,n-1);
	t=clock()-t;
	printf("MergeSort	time:%fs	correct:", ((double)t)/CLOCKS_PER_SEC);
	(IsCorrect(temp, n))? cout <<"true\n":cout <<"false\n";
	for (int i=0; i<n; i++)
		temp[i]=arr[i];
	t=clock();
	InsertionSort(temp, n);
	t=clock()-t;
	printf("InsertSort	time:%fs	correct:", ((double)t)/CLOCKS_PER_SEC);
	(IsCorrect(temp, n))? cout <<"true\n":cout <<"false\n";
	for (int i=0; i<n; i++)
		temp[i]=arr[i];
	t=clock();
	QuickSort(temp,0,n-1);
	t=clock()-t;
	printf("QuickSort	time:%fs	correct:", ((double)t)/CLOCKS_PER_SEC);
	(IsCorrect(temp, n))? cout <<"true\n":cout <<"false\n";
	for (int i=0; i<n; i++)
		temp[i]=arr[i];
	t=clock();
	RadixSort(temp,n);
	t=clock()-t;
	printf("RadixSort	time:%fs	correct:", ((double)t)/CLOCKS_PER_SEC);
	(IsCorrect(temp, n))? cout <<"true\n":cout <<"false\n";
	for (int i=0; i<n; i++)
		temp[i]=arr[i];
	t=clock();
	HeapSort(temp,n);
	t=clock()-t;
	printf("HeapSort	time:%fs	correct:", ((double)t)/CLOCKS_PER_SEC);
	(IsCorrect(temp, n))? cout <<"true\n":cout <<"false\n";
	for (int i=0; i<n; i++)
		temp[i]=arr[i];
	t=clock();
	qsort(temp,n,sizeof(int),compare);
	t=clock()-t;
	printf("qsort		time:%fs	correct:", ((double)t)/CLOCKS_PER_SEC);
	(IsCorrect(temp, n))? cout <<"true\n":cout <<"false\n"; 
	delete[] arr;
	delete [] temp;
	system("pause");
	return 0;
}
#include <iostream>
using namespace std;

int partion (int* arr, int p, int r){
	int x=arr[p];
	int i=p-1;
	int j=r+1;
	while(true){
		do
		--j;
		while(arr[j]>x);
		do
		++i;
		while(arr[i]<x);
		if(i<j)
			swap(arr[i],arr[j]);
		else return j;
	}
}


void QuickSort (int* arr, int p, int r, int k){
	if(p<r){
		int q=partion(arr, p,r);
		if (k<=q)
		QuickSort(arr, p,q, k);
		else
		QuickSort(arr, q+1, r, k);
	}
}	

int main(){
	int n,k;
	cin >>n;
	cin >>k;
	int* arr=new int [n];
	for (int i=0; i<n; ++i)
		cin >>arr[i];
	QuickSort(arr, 0, n-1, k-1);
	cout << arr[k-1]<< endl;
	delete [] arr;
	system ("pause");
	return 0;
}

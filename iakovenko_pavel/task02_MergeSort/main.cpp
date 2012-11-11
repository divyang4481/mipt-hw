#include <iostream>
using namespace std;

void Merge (int* arr, int p, int q, int r){
	int* temp=new int [r-p+1];
	int i=0, k=p, j=q+1;
	while(k<=q && j<=r && i<r-p+1){
		if (arr[k]<=arr[j]){
			temp[i]=arr[k];
			++k;}
		else{
			temp[i]=arr[j];
			++j;
		}
		++i;
	}
	if (k>q)
		for(;i<r-p+1;i++,j++)
			temp[i]=arr[j];
	else if (j>r)
		for(;i<r-p+1;i++,k++)
			temp[i]=arr[k];
	for (int i=0; i<r-p+1; i++)
		arr[p+i]=temp[i];
}

void MergeSort (int* arr, int p, int r){
	if (p<r){
		int q=(p+r)/2;
		MergeSort(arr,p,q);
		MergeSort(arr,q+1,r);
		Merge(arr,p,q,r);
	}
}	

int main(){
	int n;
	cin >> n;
	int* arr=new int [n];
	for(int i=0; i<n; ++i)
		cin >> arr[i];
	MergeSort(arr, 0, n-1);
	for(int i=0; i<n; ++i)
		cout <<arr[i] <<" ";
	delete [] arr;
	system("pause");
	return 0;
}
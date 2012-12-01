#include <iostream>
using namespace std;

void RadixSortAlg(int* arr, int n, long long int max){
	int count=1; 
	while ((max/=2)!=0)
		count++;
	int* helpArr1=new int[n];
	int* helpArr2=new int[n];
	for(int i=0; i<count; i++){
		int k,l,o; k=l=o=0;
		int mask = 1 << i;         
		for (int j=0;j<n; j++){
			if ((mask & arr[j])==0){
				helpArr1[k]=arr[j];
				k++;
			}
			else{
				helpArr2[l]=arr[j];
				l++;
			}
		}
		for(int j=0;j<k;o++,j++)
			arr[o]=helpArr1[j];
		for(int j=0;j<l;o++,j++)
			arr[o]=helpArr2[j];
	}
	delete[] helpArr1;
	delete[] helpArr2;
}
void RadixSort(int* arr, int n){
	int k,l,o; k=o=l=0;
	 int* arr1=new int [n];
	 int* arr2=new int [n];
	int max1=0; int max2=0;
	for(int i=0; i<n; ++i){
		if (arr[i]>=0){
			arr1[k]=arr[i];
			k++;
			if(arr[i]>max1) max1=arr[i];
		}
		else{
			arr2[l]=arr[i];
			l++;
			if(arr[i]<max2) max2=arr[i];
		}
		
	}
	if (k>0)
	RadixSortAlg(arr1, k, max1);
	if (l>0)
	RadixSortAlg(arr2, l, max2);
	for(int i=0; i<l; ++i, o++)
		arr[o]=arr2[i];
	for(int i=0; i<k; ++i,o++)
		arr[o]=arr1[i];
	delete [] arr1;
	delete [] arr2;
}
void Merge (int* arr, int p, int q, int r, int* temp){
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

void MergeSortAlg (int* arr, int p, int r, int* temp){
	if (p<r){
		int q=(p+r)/2;
		MergeSortAlg(arr,p,q, temp);
		MergeSortAlg(arr,q+1,r, temp);
		Merge(arr,p,q,r, temp);
	}
}	

void MergeSort(int* arr, int p, int r){
	int* temp=new int [r-p+1];
	MergeSortAlg(arr, p, r ,temp);
	delete[] temp;
}

void InsertionSort(int* arr, int n){
	for(int j=1; j<n;j++){
		int key=arr[j];
		int i=j-1;
		while(i>=0 && arr[i]>key){
			arr[i+1]=arr[i];
			i--;
		}
		arr[i+1]=key;
	}
}



int Parent(int i){
	return i/2;
}
int LeftChild(int i){
	return 2*i;
}
int RightChild(int i){
	return 2*i+1;
}

void Heapify(int* arr, int n, int i){
	int l=LeftChild(i);
	int r=RightChild(i);
	int largest;
	if (l<=n-1 && arr[l]>arr[i])
		largest=l;
	else
		largest=i;
	if (r<=n-1 && arr[r]>arr[largest])
		largest=r;
	if(largest!=i){
		swap(arr[i],arr[largest]);
		Heapify(arr,n,largest);
	}
}

void BuildHeap(int* arr, int n){
	for (int i=n/2-1;i>=0;--i)
		Heapify(arr,n,i);
}

void HeapSort(int* arr,int n){
	BuildHeap(arr, n);
	for (int i=n-1;i>0; --i){
		swap(arr[0],arr[i]);
		--n;
		Heapify(arr,n, 0);
	}
}

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


void QuickSort (int* arr, int p, int r){
	if(p<r){
		int q=partion(arr, p,r);
		QuickSort(arr, p,q);
		QuickSort(arr, q+1, r);
	}
}	
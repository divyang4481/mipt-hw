#include <iostream>
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

void MergeSort (int* arr, int p, int r){
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

void QuickSort(int l, int r, int *buf){
    int i=l,j=r,k=(l+r)/2,x=buf[k];
    do
    {
     while (buf[i]<x) ++i;
     while (buf[j]>x) --j;
     if (i<=j)
     {
         int b=buf[i];
         buf[i]=buf[j];
         buf[j]=b;
         ++i;--j;
     }
    }
    while (i<=j);
    if (i<r) QuickSort(i,r,buf);
    if (j>l) QuickSort(l,j,buf);
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
	MergeSort(temp,0, n-1);
	t=clock()-t;
	printf("MergeSort	time:%fs	correct:", ((double)t)/CLOCKS_PER_SEC);
	(IsCorrect(temp, n))? cout <<"true\n":cout <<"false\n";
	/*for (int i=0; i<n; i++)
		temp[i]=arr[i];
	t=clock();
	InsertionSort(temp, n);
	t=clock()-t;
	printf("InsertSort	time:%fs	correct:", ((double)t)/CLOCKS_PER_SEC);
	(IsCorrect(temp, n))? cout <<"true\n":cout <<"false\n";*/
	for (int i=0; i<n; i++)
		temp[i]=arr[i];
	t=clock();
	QuickSort(0, n-1, temp);
	t=clock()-t;
	printf("QuickSort	time:%fs	correct:", ((double)t)/CLOCKS_PER_SEC);
	(IsCorrect(temp, n))? cout <<"true\n":cout <<"false\n";
	/*for (int i=0; i<n; i++)
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
	(IsCorrect(temp, n))? cout <<"true\n":cout <<"false\n"; */
	for (int i=0; i<n; i++)
		temp[i]=arr[i];
	t=clock();
	qsort((void*)temp,n,sizeof(int),compare);
	t=clock()-t;
	printf("qsort		time:%fs	correct:", ((double)t)/CLOCKS_PER_SEC);
	(IsCorrect(temp, n))? cout <<"true\n":cout <<"false\n"; 
	delete[] arr;
	delete [] temp;
	system("pause");
	return 0;
}
#include <iostream>
#include <time.h>
using namespace std;


class TQueue {
	float* arr;
	int size;
	int Parent(int i){
		return i/2;
	}
	int LeftChild(int i){
		return 2*i;
	}
	int RightChild(int i){
		return 2*i+1;
	}

	void Heapify(int i){
		int l=LeftChild(i);
		int r=RightChild(i);
		int largest;
		if (l<=size-1 && arr[l]<arr[i])
			largest=l;
		else
			largest=i;
		if (r<=size-1 && arr[r]<arr[largest])
			largest=r;
		if(largest!=i){
			swap(arr[i],arr[largest]);
			Heapify(largest);
		}
	}

	void BuildHeap(){
		for (int i=size/2-1;i>=0;--i)
			Heapify(i);
	}
public:
	TQueue(float* tarr, int tsize){
		arr=tarr;
		size=tsize;
		BuildHeap();
	}
	
	float Extract_min (){
		float temp=arr[0];
		swap(arr[0], arr[size-1]);
		size--;
		Heapify(0);
		return temp;
	}
	 void Insert (float temp){
		 int i=size;
		 size++;
		 arr[i]=temp;
		 while (arr[i]>arr[Parent(i)]){
			 swap(arr[i], arr[Parent(i)]);
			 i=Parent(i);
		 }
	 }
};

float Queue_Sum(float* arr, int size){
	float t1,t2;
	TQueue temp( arr, size);
	while(size!=1){
		t1=temp.Extract_min();
		t2=temp.Extract_min();
		temp.Insert(t1+t2);
		size--;
	}
	return arr[0];
}




float Kahan_Sum (float* arr, int n){
	float sum = 0.0;
    float c = 0.0;
	float y, t1;
    for(int i = 0; i<n;++i){
        y = arr[i] - c;    
        t1 = sum + y;        
        c = (t1 - sum) - y;   
        sum = t1;
	}
	return sum;
}





int main(){
	int n;
	cin >>n;
	float* arr=new float[n];
	for(int i=0; i<n; i++)
		cin>>arr[i];
	int t=clock();
	cout << Kahan_Sum(arr,n) <<'\t'<< (float)(clock()-t)/CLOCKS_PER_SEC<< " sec"<< endl;
	t=clock();
	cout << Queue_Sum(arr, n) <<'\t'<< (float)(clock()-t)/CLOCKS_PER_SEC<< " sec"<< endl;
	delete [] arr;
	system("pause");
	return 0;
	} 

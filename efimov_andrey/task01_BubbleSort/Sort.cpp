#include <iostream>

using namespace std;

void swap(int* a, int* b){
	int t;
	t=*a;
	*a=*b;
	*b=t;
}

void BubbleSort(int* p, int n){  
	for (int i=1; i<=n; i++){
        for (int j=0; j<n-i; j++){
            if (*(p+j)>*(p+j+1)){
                swap((p+j),(p+j+1));
            };
        };
    };
}

int main(){
	freopen ("in.txt", "rt", stdin);
	freopen ("out.txt", "wt", stdout);
	int n;
	cin >> n; 
	int* ar=new int[n];
	for (int i=0; i<n; i++){
		cin >> *(ar+i);
	}
	BubbleSort(ar, n);
	for (int i=0; i<n; i++){
		cout << *(ar+i) << " ";
	}
	delete[] ar;
	return 0;
}
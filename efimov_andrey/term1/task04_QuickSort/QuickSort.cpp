#include <iostream>

using namespace std;

int partition(int* a, int p, int r){
	int me = a[r];
	while ( p < r ){
		while (a[p]<me)
			p++;
		while (a[r]>me)
			r--;
		if (a[p]==a[r])
			p++;
		else if ( p < r ){
			int t = a[p];
			a[p] = a[r];
			a[r] = t;
		}
	}
	return r;
}

void quicksort(int* input, int p, int r){
	if ( p < r ){
		int j = partition(input, p, r);        
		quicksort(input, p, j-1);
		quicksort(input, j+1, r);
    }
}

int main(){
	int n;
	cin >> n;
	int* a = new int[n];
	for (int i=0; i<n; i++)
		cin >> a[i];
	quicksort(a, 0, n-1);
	for (int i=0; i<n; i++)
		cout << a[i] << " ";
	return 0;
}
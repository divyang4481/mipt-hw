#include <iostream>

using namespace std;

int partition(int* a, int p, int r){
	int me = a[rand()%(r-p)+p];
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

void halfsort(int* input, int p, int r, int k){
	if ( p < r ){
		int j = partition(input, p, r);        
		if (k<j) halfsort(input, p, j-1, k);
		if (k>j) halfsort(input, j+1, r, k);
    }
}

int main(){
	int k, n;
	cin >> n;
	cin >> k;
	int*a = new int[n];
	for (int i=0; i<n; i++){
		cin >> a[i];
	}
	halfsort (a, 0, n, k);
	cout << a[k];
	return 0;
}
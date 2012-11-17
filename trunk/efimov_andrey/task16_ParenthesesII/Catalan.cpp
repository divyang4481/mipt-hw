#include <iostream>

using namespace std;

int C(int n, int k){
	int c=1;
	for (int i=0; i<k; i++){
		c*=(n-i);
		c/=(i+1);
	}
	return c;
}

int main(){
	int n;
	cin >> n;
	cout << C(2*n,n)/(n+1);
}
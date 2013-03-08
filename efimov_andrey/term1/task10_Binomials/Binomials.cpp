#include <iostream>

using namespace std;

int main(){
	int n, c=1;
	cin >> n;
	cout << c << " ";
	for (int i=0; i<n; i++){
		c*=(n-i);
		c/=(i+1);
		cout << c << " ";
	}
}
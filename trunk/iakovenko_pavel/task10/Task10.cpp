#include <iostream>

using namespace std;

int binom (int n, int k){
	if (n==k) 
		return 1;
	return n*binom(n-1, k)/(n-k);
}

int main(){
	int n;
	cin >> n;
	for (int i=0; i<=n; ++i)
		cout << binom(n, i)<< endl;	
	system("pause");
	return 0;
}
	

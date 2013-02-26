#include <iostream>
using namespace std;

long long int catalan (int n){
	long long int cat=1;
	for (int i=0; i<n; i++){
		cat*=2*n-i;
		cat/=i+1;
	}
	return cat/(n+1);
}

int main(){
	int n;
	cin >> n;
	cout << catalan(n)<< endl;
	system("pause");
	return 0;
}
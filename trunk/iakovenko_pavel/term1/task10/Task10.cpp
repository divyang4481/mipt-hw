#include <iostream>
using namespace std;

int main(){
	int n;
	cin >> n;
	long long int b=1;
	for (int i=0; i<n+1; i++){
		cout << b<< endl;
		b*=n-i;
		b/=i+1;
	}
	system("pause");
	return 0;
}
	

#include <iostream>

using namespace std;

int main(){
	int n, r;
	bool f=true;
	cin >> n;
	r=sqrt((double)n);
	for (int i=2; i<=r; i++){
		if (n%i==0) f=false;
	}
	if (f) cout << "YES";
	else cout << "NO";
	cin >> n;
	return 0;
}
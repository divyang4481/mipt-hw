#include <iostream>

using namespace std;

int main(){
	float sum=0.0, c, t, p=0.0;
	int n;
	cin >> n;
	float* a=new float [n];
	for (int i=0; i<n; i++)
		cin >> a[i];
	for (int i=0; i<n; i++){
		c=a[i]-p;
		t=sum+c;
		p=(t-sum)-c;
		sum=t;
	}
	cout << sum;
	return 0;
}
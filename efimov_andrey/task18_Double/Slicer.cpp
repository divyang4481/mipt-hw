#include <iostream>
using namespace std;

void PrintMem(const void *ptr, int size){
	int s=size*8;
	long long *c=(long long *)ptr;
	long long m = 1LL << (s-1);
	while (s){
		if ((*c)&m) cout << 1;
		else cout << 0;
		*c = *c << 1;
		s--;
	}
	delete c;
	cout << endl;
};

int main(){
	double* a = new double;
	const void* p = a;
	cin >> *a;
	PrintMem (p, sizeof(double));
	delete a;
	return 0;
}
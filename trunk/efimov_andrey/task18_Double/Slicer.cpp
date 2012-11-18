#include <iostream>
using namespace std;

typedef union
{
    long long i;
    double d;    
} t_doubleint;


void PrintMem(const void *ptr, int size){
	int s=size*8;
	const double* c=(const double *)ptr;
	t_doubleint dl;
	dl.d=*c;
	long long m = 1LL << (s-1);
	while (s){
		if ((dl.i)&m) cout << 1;
		else cout << 0;
		dl.i = dl.i << 1;
		s--;
	}
	delete c;
	cout << endl;
};

int main(){
	freopen ("in.txt", "rt", stdin);
	freopen ("out.txt", "wt", stdout);
	double* a = new double;
	const void* p = a;
	cin >> *a;
	PrintMem (p, sizeof(double));
	delete a;
	return 0;
}
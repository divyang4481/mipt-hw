#include <iostream>
using namespace std;

int main(){
	float cf, sfr=0, sff=0;
	double cd, sdr=0, sdf=0;
	long double cl, slr=0, slf=0;
	int n;
	cin >> n;
	for (int i=1; i<=n; i+=1){
		cf=1/((float)(i*i));
		cd=1/((double)(i*i));
		cl=1/((long double)(i*i));
		sff+=cf;
		sdf+=cd;
		slf+=cl;
	}
	for (int i=n; i>0; i-=1){
		cf=1/((float)(i*i));
		cd=1/((double)(i*i));
		cl=1/((long double)(i*i));
		sfr+=cf;
		sdr+=cd;
		slr+=cl;
	}
	cout << setprecision(7) << sfr << endl;
	cout << setprecision(7) << sff << endl;
	cout << setprecision(16) << sdr << endl;
	cout << setprecision(16) << sdf << endl;
	cout << setprecision(16) << slr << endl;
	cout << setprecision(16) << slf << endl;
	return 0;
}
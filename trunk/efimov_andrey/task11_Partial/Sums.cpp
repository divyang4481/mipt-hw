#include <iostream>
#include <iomanip>
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
	cout << sfr << endl;
	cout << sff << endl;
	cout << sdr << endl;
	cout << sdf << endl;
	cout << slr << endl;
	cout << slf << endl;
	cin >> n;
	return 0;
}
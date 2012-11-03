#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	float cf, sfr=0, sff=0;
	double cd, sdr=0, sdf=0;
	long double cl, slr=0, slf=0;
	int n;
	cin >> n;
	for (float i=1; i<=n; i+=1){
		cf=1/(i*i);
		cd=1/(i*i);
		cl=1/(i*i);
		sff+=cf;
		sdf+=cd;
		slf+=cl;
	}
	for (float i=n; i>0; i-=1){
		cf=1/(i*i);
		cd=1/(i*i);
		cl=1/(i*i);
		sfr+=cf;
		sdr+=cd;
		slr+=cl;
	}
	cout << setprecision (15) << sfr << endl;
	cout << setprecision (15) << sff << endl;
	cout << setprecision (15) << sdr << endl;
	cout << setprecision (15) << sdf << endl;
	cout << setprecision (15) << slr << endl;
	cout << setprecision (15) << slf << endl;
	return 0;
}
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
		cf=(float)i;
		cd=(double)i;
		cl=(long double)i;
		sff+=1/(cf*cf);
		sdf+=1/(cd*cd);
		slf+=1/(cl*cl);
	}
	for (int i=n; i>0; i-=1){
		cf=(float)i;
		cd=(double)i;
		cl=(long double)i;
		sfr+=1/(cf*cf);
		sdr+=1/(cd*cd);
		slr+=1/(cl*cl);
	}
	cout << setprecision(7) << sfr << endl;
	cout << setprecision(7) << sff << endl;
	cout << setprecision(16) << sdr << endl;
	cout << setprecision(16) << sdf << endl;
	cout << setprecision(16) << slr << endl;
	cout << setprecision(16) << slf << endl;
	return 0;
}

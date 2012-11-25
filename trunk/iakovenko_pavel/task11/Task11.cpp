#include <iostream>
#include <math.h>
#include <cstdio>
using namespace std;

int main(){
	float n;
	cin >> n;
	float sumf1=0.0, sumf2=0.0;
	for(float i=0.0; i<n;++i)
		sumf1+=1/((i+1)*(i+1));
	for (float i=n-1; i>=0; --i)
		sumf2+=1/((i+1)*(i+1));
	printf("%.7f\n", sumf1);
	printf("%.7f\n", sumf2);

	double sumd1=0.0, sumd2=0.0;
	for(double i=0.0; i<n;++i)
		sumd1+=1/((i+1)*(i+1));
	for(double i=n-1; i>=0.0; --i)
		sumd2+=1/((i+1)*(i+1));
	printf("%.15f\n", sumd1);
	printf("%.15f\n", sumd2);


	long double sumld1=0.0, sumld2=0.0;
	for(long double i=0.0; i<n;++i)
		sumld1+=1/((i+1)*(i+1));
	for(long double i=n-1; i>=0; --i)
		sumld2+=1/((i+1)*(i+1));
	printf("%.31Lf\n", sumld1);
	printf("%.31Lf\n", sumld2);
	//system ("pause");
	return 0;
}
	



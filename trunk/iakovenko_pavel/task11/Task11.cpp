#include <iostream>
#include <iostream>
#include <math.h>
using namespace std;

int main(){
	int n;
	scanf_s("%d",&n);
	float sumf1,sumf2; sumf1=sumf2=0.0;
	float* numb = new float[n];
	for(int i=0; i<n;++i){
		numb[i]=1/(pow(((float)i+1.0),2));
		sumf1+=numb[i];
	}
	for (int i=n-1; i>=0; --i)
	sumf2+=numb[i];
	printf_s("%.20f\n", sumf1);
	printf_s("%.20f\n", sumf2);

	double sumd1,sumd2; sumd1=sumd2=0.0;
	double* numb1 = new double[n];
	for(int i=0; i<n;++i){
		numb1[i]=1/(pow(((double)i+1.0),2));
		sumd1+=numb1[i];
	}
	for (int i=n-1; i>=0; --i)
	sumd2+=numb1[i];
	printf_s("%.20f\n", sumd1);
	printf_s("%.20f\n", sumd2);

	long double sumld1,sumld2; sumld1=sumld2=0.0;
	long double* numb2 = new long double[n];
	for(int i=0; i<n;++i){
		numb2[i]=1/(pow(((long double)i+1.0),2));
		sumld1+=numb2[i];
	}
	for (int i=n-1; i>=0; --i)
	sumld2+=numb2[i];
	printf_s("%.20f\n", sumld1);
	printf_s("%.20f\n", sumld2);
	return 0;
}
	



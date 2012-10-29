#include <iostream>
#include <math.h>
using namespace std;

int main(){
	int n;
	scanf("%d",&n);
	float sumf1,sumf2; sumf1=sumf2=0.0;
	float* numb = new float[n];
	for(int i=0; i<n;++i){
		numb[i]=1/(pow(((float)i+1.0),2));
		sumf1+=numb[i];
	}
	for (int i=n-1; i>=0; --i)
	sumf2+=numb[i];
	printf("%.7f\n", sumf1);
	printf("%.7f\n", sumf2);

	double sumd1,sumd2; sumd1=sumd2=0.0;
	double* numb1 = new double[n];
	for(int i=0; i<n;++i){
		numb1[i]=1/(pow(((double)i+1.0),2));
		sumd1+=numb1[i];
	}
	for (int i=n-1; i>=0; --i)
	sumd2+=numb1[i];
	printf("%.16f\n", sumd1);
	printf("%.16f\n", sumd2);

	long double sumld1,sumld2; sumld1=sumld2=0.0;
	long double* numb2 = new long double[n];
	for(int i=0; i<n;++i){
		numb2[i]=1/(pow(((long double)i+1.0),2));
		sumld1+=numb2[i];
	}
	for (int i=n-1; i>=0; --i)
	sumld2+=numb2[i];
	printf("%.16f\n", sumld1);
	printf("%.16f\n", sumld2);
	system ("pause");
	return 0;
}
	



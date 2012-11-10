#include <iostream>
#include <math.h>
using namespace std;

int main(){
	int n;
	cin >> n;
	float sumf1=0.0, sumf2=0.0;
	float* numb = new float[n];
	for(int i=0; i<n;++i){
		numb[i]=1/((float)((i+1)*(i+1)));
		sumf1+=numb[i];
	}
	for (int i=n-1; i>=0; --i)
	sumf2+=numb[i];
	printf("%.7f\n", sumf1);//float у меня выдает 16 значащих знаков после запятой
	printf("%.7f\n", sumf2);
	free(numb);

	double sumd1=0.0, sumd2=0.0;
	double* numb1 = new double[n];
	for(int i=0; i<n;++i){
		numb1[i]=1/((double)((i+1)*(i+1)));
		sumd1+=numb1[i];
	}
	for (int i=n-1; i>=0; --i)
	sumd2+=numb1[i];
	printf("%.15f\n", sumd1);
	printf("%.15f\n", sumd2);
	free(numb1);

	long double sumld1=0.0, sumld2=0.0;
	long double* numb2 = new long double[n];
	for(int i=0; i<n;++i){
		numb2[i]=1/((long double)((i+1)*(i+1)));
		sumld1+=numb2[i];
	}
	for (int i=n-1; i>=0; --i)
	sumld2+=numb2[i];
	printf("%.31lf\n", sumld1);
	printf("%.31lf\n", sumld2);
	free(numb2);
	system ("pause");
	return 0;
}
	



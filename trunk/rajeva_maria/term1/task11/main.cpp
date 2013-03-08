#include "cstdio"
#include <iostream>
 using namespace std;
int main()
{   int n = 0;
    float s1=0;
	float s2=0;
	double s3=0;
	double s4=0;
	long double s5=0;
	long double s6=0;
	scanf("%d",&n);
	for (int i=1;i<n+1;++i)
	{
		s1=s1+1/((float)i*(float)i);
		s2=s2+1/((float)(n+1-i)*(float)(n-i+1));
		s3=s3+1/((double)i*(double)i);
		s4=s4+1/((double)(n+1-i)*(double)(n-i+1));
        s5=s5+1/((long double)i*(long double)i);
		s6=s6+1/((long double)(n+1-i)*(long double)(n-i+1));

	}
	printf("%.7f\n",s1);
	printf("%.7f\n",s2);
	printf("%.16f\n",s3);
	printf("%.16f\n",s4);
	printf("%.16f\n",s5);
	printf("%.16f\n",s6);
	
	return 0;
}

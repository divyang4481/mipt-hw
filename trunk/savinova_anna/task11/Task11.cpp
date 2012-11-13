#include "cstdio"


int main()
{
	int N = 0;
    scanf("%d", &N);    
    float SUMF1 = 0;
    for (float i = 1; i < N+1; ++i)
        SUMF1 += 1 / (i * i);
    printf("%.7f\n", SUMF1);
    float SUMF2 = 0;
    for (float i = N; i > 0; --i)
        SUMF2 += 1 / (i * i);
    printf("%.7f\n", SUMF2);    
    double SUMD1 = 0;
    for (double i = 1; i < N+1; ++i)
        SUMD1 += 1 / (i * i);
    printf("%.16f\n", SUMD1);
    double SUMD2 = 0;
    for (double i = N; i > 0; --i)
        SUMD2 += 1 / (i * i);
    printf("%.16f\n", SUMD2);
    long double SUMLD1 = 0;
    for (long double i = 1; i < N+1; ++i)
        SUMLD1 += 1 / (i * i);
    printf("%.16f\n", SUMLD1);
    long double SUMLD2 = 0;
    for (long double i = N; i > 0; --i)
        SUMLD2 += 1 / (i * i);
    printf("%.16f\n", SUMLD2);
    return 0;
}
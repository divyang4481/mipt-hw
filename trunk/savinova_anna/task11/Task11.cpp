#include "stdafx.h"
#include "cstdio"


int main()
{
	int N = 0;
    scanf("%d", &N);
    float* F = new float[N+1];
    for (int i = 1; i <= N; ++i)
        F[i] = (i^(-2));
    float SUMF1 = 0;
    for (int i = 1; i <= N; ++i)
        SUMF1 += F[i];
    printf("%.20f\n", SUMF1);
    float SUMF2 = 0;
    for (int i = N; i >= 1; --i)
        SUMF2 += F[i];
    printf("%.20f\n", SUMF2);
    delete[] F;
    double* D = new double[N+1];
    for (int i = 1; i <= N; ++i)
        D[i] = 1 / (i * i);
    double SUMD1 = 0;
    for (int i = 1; i <= N; ++i)
        SUMD1 += D[i];
    printf("%.20f\n", SUMD1);
    double SUMD2 = 0;
    for (int i = N; i >= 1; --i)
        SUMD2 += D[i];
    printf("%.20f\n", SUMD2);
    delete[] D;
    long double* LD = new long double[N+1];
    for (int i = 1; i <= N; ++i)
        LD[i] = 1 / (i * i);
    double SUMLD1 = 0;
    for (int i = 1; i <= N; ++i)
        SUMLD1 += LD[i];
    printf("%.20f\n", SUMLD1);
    double SUMLD2 = 0;
    for (int i = N; i >= 1; --i)
        SUMLD2 += LD[i];
    printf("%.20f\n", SUMLD2);
    delete[] LD;
    return 0;
}


#define  _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const double Pi = acos(-1.0);

template < typename T >
T getIncSum(int n) {
    T sum = 0.0;
    for (int i = 1; i <= n; ++i)
        sum += (T) 1.0 / i / i;
    return sum;
}

template < typename T >
T getDecSum(int n) {
    T sum = 0.0;
    for (int i = n; i > 0; --i)
        sum += (T) 1.0 / i / i;
    return sum;
}

int main() {
    int n;
    scanf("%d\n", &n);
//  printf("%.20f\n", Pi * Pi / 6);
    printf("%.20f\n%.20f\n", getIncSum<float>(n), getDecSum<float>(n));
    printf("%.20lf\n%.20lf\n", getIncSum<double>(n), getDecSum<double>(n));
    printf("%.20lf\n%.20lf\n", getIncSum<long double>(n), getDecSum<long double>(n));
    return 0;
}

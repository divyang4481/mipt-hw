#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

bool isPrime(int n) {
    if (n == 2)
        return true;
    if (n == 1 || n % 2 == 0)
        return false;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;
    return true;
}

int main() {
    int N;
    scanf("%d\n", &N);
    if (isPrime(N))
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef unsigned long long ull;

int main() {
    ull N;
    cin >> N;
    ull coefficient = 1;
    for (ull k = 0; k <= N; ++k) {
        cout << coefficient << endl;
        coefficient *= (N - k);
        coefficient /= (k + 1);
    }
    return 0;
}
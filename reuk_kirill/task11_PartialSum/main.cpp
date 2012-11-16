#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

using namespace std;

int main()
{

    float ff = 0, fb = 0;
    double df = 0, db = 0;;
    long double ldf = 0, ldb = 0;

    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
    {
        ff += (float)(1/pow(i, 2.0));
        df += (double)(1/pow(i, 2.0));
        ldf += (long double)(1/pow(i, 2.0));
    }

    for (int i = n; i > 0; --i)
    {
        fb += (float)(1/pow(i, 2.0));
        db += (double)(1/pow(i, 2.0));
        ldb += (long double)(1/pow(i, 2.0));
    }

    cout << ff << endl;
    cout << fb << endl;
    cout << df << endl;
    cout << db << endl;
    cout << ldf << endl;
    cout << ldb << endl;
    return 0;
}

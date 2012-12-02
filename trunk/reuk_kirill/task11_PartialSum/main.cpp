#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <limits>

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
        ff += (float)(1.0/(i*i));
        df += (double)(1.0/(i*i));
        ldf += (long double)(1.0/(i*i));
    }

    for (int i = n; i > 0; --i)
    {
        fb += (float)(1.0/(i*i));
        db += (double)(1.0/(i*i));
        ldb += (long double)(1.0/(i*i));

    }

    /*int prec = numeric_limits<float>::digits10;
    printf("%d ", prec);
    prec = numeric_limits<double>::digits10;
    printf("%d ", prec);
    prec = numeric_limits<long double>::digits10;
    printf("%d", prec);*/

    cout << setprecision(6) << ff << endl;
    cout << setprecision(6) << fb << endl;
    cout << setprecision(15) << df << endl;
    cout << setprecision(15) << db << endl;
    cout << setprecision(18) << ldf << endl;
    cout << setprecision(18) << ldb << endl;

    return 0;
}

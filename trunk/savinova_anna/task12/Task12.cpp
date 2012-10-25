// Task12.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "time.h"
#include <iostream>

using namespace std;


int main()
{
    int N = 0;
    cin >> N;
    double* Ar = new double[N];
    for (int i = 0; i < N; ++i)
        cin >> Ar[i];    
	int t = clock();
    double e = 0.0;
    double sum = 0.0;
    for (int i = 0; i < N; ++i ) 
    {
        const double y = Ar[i] - e;
        const double tmp = sum + y;
        e = (tmp - sum) - y;   
        sum = tmp;
    }
    int t1 = clock() - t;
    cout << sum << " " << (float)t1/CLOCKS_PER_SEC;
    return 0;
}
// Task12.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "time.h"
#include <queue>
#include <iostream>

using namespace std;

int Compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

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
    priority_queue (Compare()) pq;
    cout << 
    return 0;
}
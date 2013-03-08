#include "time.h"
#include <queue>
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
    double sum1 = 0.0, sum2 = 0.0;
    for (int i = 0; i < N; ++i ) 
    {
        const double y = Ar[i] - e;
        const double tmp = sum1 + y;
        e = (tmp - sum1) - y;   
        sum1 = tmp;
    }
    int t1 = clock() - t;
    cout << sum1 << " " << (double)t1/CLOCKS_PER_SEC << endl;
    priority_queue <double, vector<double>, greater<double> > PQ;
    for (int i = 0; i < N; ++i)
        PQ.push(Ar[i]);    
    t = clock();
    for (int i = 0; i < N; ++i)
    {
        sum2 += PQ.top();
        PQ.pop();
    }
    t1 = clock() - t;
    cout << sum2 << " " << (double)t1/CLOCKS_PER_SEC << endl;
    delete[] Ar;
    return 0;
}
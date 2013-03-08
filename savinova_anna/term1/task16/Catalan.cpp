#include <iostream>

using namespace std;

int cnk(int n, int k)
{
    if (n==k) return 1;
    return (n * cnk(n-1, k))/(n-k);
}
    
int main()
{
    int N = 0;
    cin >> N;
    cout << cnk(2*N,N)/(N+1) << endl;
    return 0;
}
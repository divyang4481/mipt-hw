#include <iostream>
using namespace std;

int main()
{
    int N = 0;
    cin >> N;
    int cnk = 1;
    for (int k = 0; k <= N; ++k)
    {
        cout << cnk << endl;
        cnk = cnk * (N - k) / (k + 1);
    }
    return 0;
}
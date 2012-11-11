#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int res=1;
    cout << res << ' ';
    for (int i=0;i<n;++i)
     {
         res*=(n-i);
         res/=(i+1);
         cout << res << ' ';
     }
    return 0;
}

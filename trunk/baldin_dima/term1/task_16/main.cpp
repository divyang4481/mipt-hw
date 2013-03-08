#include <iostream>

using namespace std;

int Cat(int n)
{
    int c = 1;
    for (int i=n;i<2*n;++i)
     c*=(i+1);
    for (int i=0;i<=n;++i)
     c/=(i+1);
    return c;

}
int main()
{
    int n;
    cin >> n;
    cout << Cat(n);
    return 0;
}

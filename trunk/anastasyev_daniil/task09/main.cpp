#include <iostream>
using namespace std;

bool Prime(long n)
{
    if (n<1) return false;
    if ((n==1) || (n==2)) return true;
    for (int i=2; i*i<=n; ++i) if (n % i==0) return false; 
    return true;
}

int main()
{
    long n;
    cin >> n;
    if (Prime(n)) cout << "YES";
    else printf("NO");
    return 0;
}
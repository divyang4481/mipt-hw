#include <iostream>
#include <math.h>
using namespace std;

bool PrimeNumber(int n)
{
    int s=(sqrt(n))+1;
    if (n==1)
    return false;
    else {
           for (int i=2;i<s;++i)
            if (n%i==0)
            return false;
         }
    return true;
}
int main()
{
    int n;
    cin >> n;
    cout << ((PrimeNumber(n))||(n==2)?"YES":"NO");



    return 0;
}

#include <iostream>
#include <limits>
#include <iomanip>
using namespace std;

int main()
{
    int n;
    cin >> n;
    float rfup=0.0,rfdown=0.0, rf;
    double rdup=0.0,rddown=0.0, rd;
    long double rldup=0.0,rlddown=0.0, rld;
    //up
    for (int i=1;i<=n;++i)
     {
         rf = (float)i;
         rd = (double)i;
         rld = (long double)i;
         rfup+=1.0/(rf * rf);
         rdup+=1.0/(rd * rd);
         rldup+=1.0/(rld * rld);
     }
    //down
    for (int i=n;i>=1;--i)
     {
         rf = (float)i;
         rd = (double)i;
         rld = (long double)i;
         rfdown+=1.0/(rf * rf);
         rddown+=1.0/(rd * rd);
         rlddown+=1.0/(rld * rld);
     }

    cout << setprecision(numeric_limits<float>::digits10)  << rfup << " float up" << "\n";
    cout << setprecision(numeric_limits<float>::digits10)  << rfdown << " float down" << "\n";
    cout << setprecision(numeric_limits<double>::digits10) << rdup << " double up" << "\n";
    cout << setprecision(numeric_limits<double>::digits10) << rddown << " double up" << "\n";
    cout << setprecision(numeric_limits<long double>::digits10) << rldup << " long double up" << "\n";
    cout << setprecision(numeric_limits<long double>::digits10) << rlddown << " long double down" << "\n";
    return 0;
}

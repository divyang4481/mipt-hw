#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    float rfup=0.0,rfdown=0.0;
    double rdup=0.0,rddown=0.0;
    long double rldup=0.0,rlddown=0.0;
    //up
    for (int i=1;i<=n;++i)
     {
         rfup+=1.0/float(i*i);
         rdup+=1.0/double(i*i);
         rldup+=1.0/(long double)(i*i);
     }
    //down
    for (int i=n;i>=1;--i)
     {
         rfdown+=1.0/float(i*i);
         rddown+=1.0/double(i*i);
         rlddown+=1.0/(long double)(i*i);
     }
    cout << rfup << " float up" << "\n";
    cout << rfdown << " float down" << "\n";
    cout << rdup << " double up" << "\n";
    cout << rddown << " double up" << "\n";
    cout << rldup << " long double up" << "\n";
    cout << rlddown << " long double down" << "\n";
    return 0;
}

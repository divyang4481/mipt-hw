#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
    long long n;
    cin>>n;
    float s=0.0;
	for(float i=1;i<n+1;++i)s+=1/(i*i);
    cout<<fixed<<setprecision(7)<<s;
    cout<<'\n';
    s=0.0;
    for(float i=n;i>0;--i)s+=1/(i*i);
    cout<<fixed<<setprecision(7)<<s;
    cout<<'\n';
    double s1=0.0;
    for(double i=1;i<n+1;++i)s1+=1/(i*i);
    cout<<fixed<<setprecision(15)<<s1;
    cout<<'\n';
    s1=0.0;
    for(double i=n;i>0;--i)s1+=1/(i*i);   
    cout<<fixed<<setprecision(15)<<s1;
    cout<<'\n';
    long double s2=0.0;
    for(long double i=1;i<n+1;++i)s2+=1/(i*i);
    cout<<fixed<<setprecision(15)<<s2;
    cout<<'\n';
    s2=0;
    for(long double i=n;i>0;--i)s2+=1/(i*i);
    cout<<fixed<<setprecision(15)<<s2;
    cout<<'\n';
    return 0;
}
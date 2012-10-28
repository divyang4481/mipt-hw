#include<iostream>
using namespace std;
int main()
{int n;
cin>>n;

float s=0.0;
for(int i=1;i<n+1;++i)s+=(float)1/(i*i);
cout<<s<<'\n';
 s=0.0;
for(int i=n;i>0;--i)s+=(float)1/(i*i);
cout<<s<<'\n';
double s1=0.0;
for(int i=1;i<n+1;++i)s1+=(double)1/(i*i);
cout<<s1<<'\n';
 s1=0.0;
for(int i=n;i>0;--i)s1+=(double)1/(i*i);
cout<<s1<<'\n';
long double s2=0.0;
for(int i=1;i<n+1;++i)s2+=(long double)1/(i*i);
cout<<s2<<'\n';s2=0;
for(int i=n;i>0;--i)s2+=(long double)1/(i*i);
cout<<s2<<'\n';
return 0;
}


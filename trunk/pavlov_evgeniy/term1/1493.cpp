#include<iostream>
using namespace std;


int f(int k){int y;y=k/100+k%10+(k/10)%10;return y;}

int main()
{
int a,b,a1,b1;
cin>>a;
a1=a+1;
a=a-1;
b=a%1000;
a=a/1000;
b1=a1%1000;
a1=a1/1000;
b=f(b);b1=f(b1);a=f(a);a1=f(a1);
if((b==a)||(b1==a1))cout<<"Yes"; else cout<<"No";
return 0;
}
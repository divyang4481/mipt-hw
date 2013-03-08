#include<iostream>
#include<string>
using namespace std;
int main()
{
	string s;
	int k=0;
	cin>>s;
	for(unsigned int i=0;i<s.length();++i)
	{
		if(s[i]=='(')++k;else --k;
		if(k<0){cout<<"NO";return 0;}
	}
	if(k!=0)cout<<"NO";else cout<<"YES";
	return 0;
}

#include<iostream>
using namespace std;
int tru(string g){
	for(int i=0;i<=g.length()/2;++i)
	{if (g[i]==g[g.length()-i-1]){} else{
			return 0;}
	
	}
	return 1;
}
int main()

{     string s,s1;	
	cin>>s;
	s1=s[0];
	long m=1;
	for(long i=1;i<=s.length();++i){
		for(long j=s.length();j-i>=m;--j){
			string ss;
			ss=s.substr(i-1,j-i+1);
			int kk;
			kk=tru(ss);
			if (kk==1) {m=j-i+1;s1=ss;}
		}
	}
	cout<<s1;
	return 0;
}

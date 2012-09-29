#include<iostream>
#include<string>
using namespace std;
int main()
{
	int k;
	string a;
	string b[1000];
	cin>>k;
	for(int i=0;i<k;++i)
		cin>>b[i];
	cin>>a;
	for(int i=0;i<k;++i){
		string c;
		c=b[i].substr(0,1);
		if(c==a)cout<<b[i]<<'\n';
	}
	return 0;}



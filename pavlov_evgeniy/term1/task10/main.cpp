#include<iostream>
using namespace std;
int main()
{
	long long o=1;
	int n;
	cin>>n;
	cout<<"1 ";
	for(int i=0;i<n;++i)
	{
		o*=n-i;
		o/=i+1;
		cout<<o<<" ";
	}
	return 0;
}


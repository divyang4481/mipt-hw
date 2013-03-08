#include"cstdio"
#include <iostream>
using namespace std;

int main()
{
	int n=0;
    scanf("%d",&n);
	int k=1;
	int t=0;
	for(int i=0;(i<n);i++)
	    {  
		t=k;
		k=k*(2*n-i)/(i+1);
		}
	printf("%d",k-t);
	system("pause");
	return 0;
}
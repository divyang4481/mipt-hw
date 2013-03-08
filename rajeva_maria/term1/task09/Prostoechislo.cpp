// Prostoechislo.cpp: определяет точку входа для консольного приложения.
//

#include <cstdio>
#include <iostream>
using namespace std;
int main()
{   int N=0; 
    int a=0;
	scanf("%d",&N);
	for (int i=2;i*i<=N;++i)
		if (N%i==0) a=1;
	if (a>0) printf("no");
		else printf ("yes");
		system("pause");
	return 0;
}


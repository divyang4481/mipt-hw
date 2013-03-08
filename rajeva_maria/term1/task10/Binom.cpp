// Binom.cpp: определяет точку входа для консольного приложения.
//

#include <cstdio>
#include <iostream>
using namespace std;


int main()
{
	int N;
	scanf("%d",&N);
	int k=1;
	printf("1 ");
	for(int i=0;i<N;i++)
	{
		k=k*(N-i)/(i+1);
		printf("%d ",k);
	}
	
	return 0;
}


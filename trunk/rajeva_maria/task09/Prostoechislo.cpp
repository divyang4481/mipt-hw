// Prostoechislo.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "cstdio"
#include "Math.h"

int main()
{   int N; 
    int a=0;
	scanf("%d",&N);
	float m=(float(N));
	for (int i=2;i<sqrt(m);++i)
		if (N%i==0) a=1;
	if (a>0) printf("no");
		else printf ("yes");
	return 0;
}


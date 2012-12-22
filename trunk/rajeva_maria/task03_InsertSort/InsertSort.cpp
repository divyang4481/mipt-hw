// InsertSort.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "cstdio"


int InsertSort(int *A, int q)
{ 
  for(int j=1;j<q;++j)
  { 
	int t=A[j];
	int i=j-1;
	while ((t<A[i]) && (i>=0))
		{
			A[i+1]=A[i];
			--i;
	}
	A[i+1]=t;
  }

 return 0;
}

int main()
{   
	int N;
    scanf ("%d",&N);
	int *Ar= new int[N];
	for (int i=0; i<N;++i)
	{
		scanf("%d",&Ar[i]);

	}
	int *Ar1= new int[N];
	InsertSort(Ar,N);
	for (int i=0; i<N;++i)
	printf("%d ",Ar[i]);
	delete[]Ar;
	return 0;

}


// Binom.cpp: определяет точку входа для консольного приложения.
//

int Bin(int *A,int k)
   {int *B=new int[10];
     B[0]=1;
	 B[k]=1;
	 for (int i=1;i<k;++i)
	 {
		 B[i]=A[i]+A[i-1];
	 }
	 for (int i=0;i<k+1;++i)
	 {
		 A[i]=B[i];
	 }
	 return 0;
   }

int main()
{
	int N;
	scanf("%d",&N);
	int *Ar=new int[N];
	Ar[0]=1;
	Ar[1]=1;
	for (int i=2;i<N+1;++i)
		Bin(Ar,i);
	for(int i=0;i<N+1;i++)
	{printf("%d",Ar[i]);
	printf(" ");
	}
	return 0;
}


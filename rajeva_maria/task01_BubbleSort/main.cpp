// Bubble.cpp: определяет точку входа для консольного приложения.
//

#include "cstdio"
#include <iostream>
 using namespace std;
int BubbleSort(int l, int r, int* a)
{
    for (int i=r-1;i>l;--i)
    {
        for (int j=0; j<i; ++j)
        {
            if (a[j]>a[j+1])
            {
                int t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
    return 0;
}  

int main()
{
    int N=0;
    scanf("%d",&N);
    int* Ar=new int[N];
    for (int i=0; i<N; ++i)
        scanf("%d",Ar+i);
    BubbleSort(1,N,Ar);
    for (int i=0; i<N; ++i)
        printf("%d ",Ar[i]);    
     delete[]Ar;
	 system("pause");
    return 0;
	
}

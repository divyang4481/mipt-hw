#include <iostream>
using namespace std;

int** Create(int h, int w)
{
    
    int** b=new int*[h];
    for (int i=0; i<h; ++i)
    {
        *(b+i)=new int[w];
    }
    return b;
}

int** Copy(int** a, int h, int w)
{
    int** b=Create(h,w);
    for (int i=0; i<h; ++i)
    {
        for (int j=0; j<w; ++j)
        {
            b[i][j]=a[i][j];
        }
    }
    return b;
}

void Delete(int **a, int h, int w)
{
    for (int i=0; i<h; ++i) delete [] a[i];
    delete [] a;
}

void CountSort(int **c, int **b, int k, int n)
{   
    int count[10];
    for (int i=0; i<=9; ++i) count[i]=0;
    for (int i=0; i<n; ++i) ++count[c[i][k]];
    for (int i=1; i<=9; ++i) count[i]+=count[i-1];
    for (int i=n-1; i>=0; --i)
    {
        b[count[c[i][k]]-1]=c[i];
        --count[c[i][k]];
    }
}

void RadixSort(int *a, int n)
{
	int MAX=a[0];
    int d=0;
	for (int i=0; i<n; ++i) if (a[i]>MAX) MAX=a[i];
	while (MAX) {MAX/=10; ++d;}
	int **c=Create(n,d);
	int **b=Create(n,d);
	for (int i=0; i<n; ++i) 
    {
		for (int j=0; j<d; ++j) {c[i][j]=a[i]%10; a[i]/=10;}
	}
	for (int i=0; i<d; ++i) 
    {
        CountSort(c,b,i,n);
        c=Copy(b,n,d);
    }
    for (int i=0; i<n; ++i)
        for (int j=0, k=1; j<d; ++j, k*=10) a[i]+=c[i][j]*k;
    Delete(c,n,d);
    Delete(b,n,d);
}

int main()
{
    int n;
	scanf("%d",&n);
	int *a=new int[n];
	for (int i=0; i<n; ++i) scanf("%d",(a+i));
	RadixSort(a, n);
    for (int i=0; i<n; ++i) printf("%d ",*(a+i));
	delete [] a;
	return 0;
}
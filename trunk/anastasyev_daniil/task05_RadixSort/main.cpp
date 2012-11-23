#include <iostream>
#include <cmath>
#include <cstdio>
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
	if (n!=0)
	{
		int count[2];
		count[0]=0; count[1]=0;
		for (int i=0; i<n; ++i) ++count[c[i][k]];
		count[1]+=count[0];
	    for (int i=n-1; i>=0; --i)
	    {
	        b[count[c[i][k]]-1]=c[i];
	        --count[c[i][k]];
	    }
	}
}

void RadixSort(int *a, int n)
{
	int MAX = a[0], d = 0;
	int n1 = 0, n2 = 0;
	for (int i=0; i<n; ++i) if (abs(a[i])>MAX) MAX=abs(a[i]);
	while (MAX) {MAX/=2; ++d;}
	int **b=Create(n,d);
    int **c=Create(n,d);
    int **temp=Create(n,d);
	for (int i=0; i<n; ++i) 
    {
		if (a[i]>0) 
        {
			for (int j=0; j<d; ++j) {b[n1][j]=a[i]%2; a[i]/=2;}
			++n1;
        }
		else 
        {
             a[i]*=-1;
             for (int j=0; j<d; ++j) {c[n2][j]=a[i]%2; a[i]/=2;}
			 ++n2;
        }
	}
	for (int i=0; i<d; ++i) 
    {
        CountSort(c,temp,i,n2);
        c=Copy(temp,n,d);
    }
 	for (int i=0; i<d; ++i) 
    {
        CountSort(b,temp,i,n1);
        b=Copy(temp,n,d);
    }   
    if (n2) for (int i=0; i<n2; ++i)
    {
        for (int j=0, k=1; j<d; ++j, k*=2) a[n2-i-1]+=c[i][j]*k;
        a[n2-i-1]*=-1;
    }
    if (n1) for (int i=0; i+n2<n; ++i)
    {
        for (int j=0, k=1; j<d; ++j, k*=2) a[i+n2]+=b[i][j]*k;
    }    
    Delete(c,n,d);
    Delete(b,n,d);
    Delete(temp,n,d);
}

int main()
{
    int n;
	scanf("%d",&n);
	int *a = new int[n];
	for (int i=0; i<n; ++i) scanf("%d",(a+i));
	RadixSort(a, n);
    for (int i=0; i<n; ++i) printf("%d ",*(a+i));
	delete [] a;
	return 0;
}

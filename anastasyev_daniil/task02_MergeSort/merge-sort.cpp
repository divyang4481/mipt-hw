# include <stdio.h>

const int N=10;

void swap(int &a, int &b)
{
	if (a>b)
	{
		int t=a;
		a=b;
		b=t;
	}
}

int Min(int *a, int &i, int &j)
{
	int t;
	if (a[i]<a[j]) 
	{
		t=a[i];
		i+=1;
	}
	else 
	{
		t=a[j];
		j+=1;
		
	}
	return t;
}

void Merge(int *a, int l, int m, int r)
{
	int c[N];
	int i=l, j=m+1;
	int k=0;
	while ((i<=m) && (j<=r))
	{
		c[k]=Min(a,i,j);
		++k;
	}
	if (i<=m) 
	{
		for (j=i; j<=m; ++j, ++k) c[k]=a[j];
	}
	else
	{
		for (i=j; i<=r; ++i, ++k) c[k]=a[i];
	}
	for (i=l, k=0; i<=r; ++i, ++k) a[i]=c[k];
}

void MergeSort(int *a, int l, int r)
{
	int m;
	if (r-l<1) {}
	else 
	{if (r-l==1)
	{
		swap(a[l],a[r]);
	}
	else 
	{
		m=(l+r)/2;
		MergeSort(a,l,m);
		MergeSort(a,m+1,r);
		Merge(a,l,m,r);
	}
	}
}

int main()
{
	int n;
	scanf("%d",&n);
	int *a=new int[n];
	for (int i=0; i<n; ++i) scanf("%d",(a+i));
	MergeSort(a,0,n-1);
	for (int i=0; i<n; ++i) printf("%d ",*(a+i));
	return 0;
}
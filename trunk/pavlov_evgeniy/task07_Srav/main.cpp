#pragma once
#include"functions.h"
#include<iostream>
#include<time.h>
using namespace std;



void rav(int *a,int *b,int n)
{
	for(long i=0;i<n;++i)b[i]=a[i];
}



int prov(int*a,int n)
{
	for(int i=0;i<n-1;++i)
		if(a[i]>a[i+1])
		{
			cout<<"false ";
			return 0;
		}
    cout<<"true ";
	return 0;
}



int main()
{
	int t,*a,*b;
	long n;
	cin>>n;
	a=new int[n];
	b=new int[n];
	for(long i=0;i<n;++i)a[i]=rand()%60000-10000;
	rav(a,b,n);
	if(n<=5000)
	{
	t=clock();
	BubbleSort(b,n);
	prov(b,n);
	cout<<"bubble   "<<((float)((clock()-t)*1000))/CLOCKS_PER_SEC<<"msec"<<'\n';
	rav(a,b,n);
	}
	else
	{
		cout<<"bubble over 100500"<<'\n';
	}
	t=clock();
	msort(b,n);
	prov(b,n);
	cout<<"merge    "<<((float)((clock()-t)*1000))/CLOCKS_PER_SEC<<"msec"<<'\n';
	rav(a,b,n);
	if(n<=5000)
	{
	t=clock();
	insertsort(b,n);
	prov(b,n);
	cout<<"insert   "<<((float)((clock()-t)*1000))/CLOCKS_PER_SEC<<"msec"<<'\n';
	rav(a,b,n);
	}
	else cout<<"insert over 100500"<<'\n';
	t=clock();
	quicksort(b,0,n-1);
	prov(b,n);
	cout<<"quick    "<<((float)((clock()-t)*1000))/CLOCKS_PER_SEC<<"msec"<<'\n';
	rav(a,b,n);
	t=clock();
	radixs(b,n);
	prov(b,n);
	cout<<"radix    "<<((float)((clock()-t)*1000))/CLOCKS_PER_SEC<<"msec"<<'\n';
	rav(a,b,n);
	t=clock();
	Heapsort(b,n);
	prov(b,n);
	cout<<"heap     "<<((float)((clock()-t)*1000))/CLOCKS_PER_SEC<<"msec"<<'\n';
	delete[] a,b;
	return 0;
}
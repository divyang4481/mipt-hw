#include <iostream>

using namespace std;

void RadixSort(int* a, int s){
	int bs[10];
	int i, m=abs(a[0]), e=1;
	for (i=1; i<s; i++)
		if (abs(a[i])>m)
			m=abs(a[i]);
	int* b = new int[s];
	while (m/e>0){
		for (i=0; i<10; i++) 
			bs[i]=0;
		for (i=0; i<s; i++) 
			bs[(abs(a[i]/e))%10]++;
		for (i=1; i<10; i++) 
			bs[i]+=bs[i-1];
		for (i = s - 1; i >= 0; i--)
			b[--bs[abs(a[i]) / e%10]] = a[i];
		for (i=0; i<s; i++)
			a[i]=b[i];
		e*=10;
	}
	delete[] b;
}

void SplitNegs(int* a, int s){
	int p, n;
	int* w = new int[s];
	n=0;
	p=s-1;
	for (int i=s-1; i>=0; i--){
		if (a[i]>=0){ 
			w[p]=a[i];
			p--;
		}
		else{
			w[n]=a[i];
			n++;
		}
	}
	for (int i=0; i<s; i++)
		a[i]=w[i];
	delete[] w;
}

int main(){
	int n;
	cin >> n;
	int* a = new int[n];
	for (int i=0; i<n; i++)
		cin >> a[i];
	RadixSort (a, n);
	for (int i=0; i<n; i++)
		cout << a[i] << " ";
	cout << endl;
	SplitNegs (a, n);
	for (int i=0; i<n; i++)
		cout << a[i] << " ";
	delete[] a;
}
#include <iostream>

using namespace std;

void RadixSort(int* a, int s){
	int bs[10];
	int i, m=a[0], e=1;
	for (i=1; i<s; i++)
		if (a[i]>m)
			m=a[i];
	int* b = new int[s];
	while (m/e>0){
		for (i=0; i<10; i++) 
			bs[i]=0;
		for (i=0; i<s; i++) 
			bs[(a[i]/e)%10]++;
		for (i=1; i<10; i++) 
			bs[i]+=bs[i-1];
		for (i = s - 1; i >= 0; i--)
			b[--bs[a[i] / e%10]] = a[i];
		for (i=0; i<s; i++)
			a[i]=b[i];
		e*=10;
	}
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
}
#include <iostream>
using namespace std;

void insertSort (int* a, int n){
	int t, j;
	for (int i=1; i<=n; i++){
		t = a[i];
		a[0]=t;
		j = i;
		while(t<a[j-1]){
			a[j]=a[j-1];
			j--;
		}
		a[j]=t;
	}
}

int main(){
	freopen ("in.txt", "rt", stdin);
	freopen ("ou.txt", "wt", stdout);
	int n;
	cin >> n;
	int* a = new int[n+1];
	for (int i=1; i<=n; i++)
		cin >> a[i];
	insertSort (a, n);
	for (int i=1; i<=n; i++)
		cout << a[i] << " ";
	delete[] a;
}
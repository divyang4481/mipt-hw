#include <iostream>

using namespace std;
const int count=100;

void swap(int* a, int* b){
	int t;
	t=*a;
	*a=*b;
	*b=t;
}

int main(){
	freopen("in.txt", "rt", stdin);
	freopen("out.txt", "wt", stdout);
	int a[count], n, m, mi, t;
	cin >> n;
	for (int i=0; i<n; i++) cin >> a[i];
	for (int i=0; i<n-1; i++){
		m=9000;
		mi=0;
		for (int j=i; j<n; j++){
			if (a[j]<m) {m=a[j]; mi=j;}
		}
		swap (a[mi], a[i]);
	}
	for(int i=0; i<n; i++){
		cout << a[i] << " ";
	}
}
#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

//support functions' names start with small letters, main sorters' with capitals

struct THeap{
	private:
		int* buf;
		int size;
		int Parent(int ix){
			return (ix-1)/2;
		}
		int lc(int ix){
			return ix+ix+1;
		}
		int rc(int ix){
			return ix+ix+2;
		}
		void BuildHeap(){
			for (int i=Parent(size-1); i>=0; --i)
				Hippefy(i);
		}
	public:
		void DecSize(){
			size--;
		}
		void Hippefy (int ix){
			int max=ix, l=lc(ix), r=rc(ix);
			if ((l<size)&&(buf[ix]<buf[l]))
				max=l;
			if ((r<size)&&(buf[max]<buf[r]))
				max=r;
			if (max!=ix){
				swap(buf[ix],buf[max]);
				Hippefy(max);
			}
		}
		THeap(int* arr, int n){
			buf = arr;
			size = n;
			BuildHeap();
		};
		void Print(){
			for (int i=0; i<size; i++)
				cout << buf[i] << " ";
		}
		int Max(){
			return buf[0];
		}
		int ExtractMax(){
			int r=buf[0];
			swap(buf[0], buf[size--]);
			Hippefy(0);
			return r;
		}
		int GetSize(){
			return size;
		}
		const int* GetBuf(){
			return buf;
		}
};

int comp		(const void* a, const void* b){
	return ( *(int*)a - *(int*)b );
}

void swap       (int* a, int* b){
	int t;
	t=*a;
	*a=*b;
	*b=t;
}

void state      (bool f){
	if (f)
		cout << "true ";
	else 
		cout << "false";
}

void name       (int  i){
	switch (i) {
	case 0:
		cout << "BubbleSort";
		break;
	case 1:
		cout << "MergeSort ";
		break;
	case 2:
		cout << "InsertSort";
		break;
	case 3:
		cout << "QuickSort ";
		break;
	case 4:
		cout << "Lib Qsort ";
		break;
	case 5:
		cout << "RadixSort ";
		break;
	case 6:
		cout << "HeapSort  ";
		break;
	}
}

bool corr       (int* a, int n){
	bool f = true;
	for (int i=1; i<n; i++){
		if (a[i-1]>a[i]) f=false;
	}
	return f;
}

int  partition  (int* a, int l, int r){
	int me = a[r];
	while (l<r){
		while (a[l]<me)
			l++;
		while (a[r]>me)
			r--;
		if (a[l]==a[r])
			l++;
		else if (l<r){
			int t = a[l];
			a[l] = a[r];
			a[r] = t;
		}
	}
	return r;
}

void splitnegs(int* a, int s){
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

void merge      (int* a, int l, int r, int* temp)
{
    int m = (l+r)/2;
    int t = 0;
    int i1 = l;
    int i2 = m + 1;
    while ( i1 <= m && i2 <= r )
        if ( a[i1] < a[i2] )
            temp[t++] = a[i1++];
        else
            temp[t++] = a[i2++];
    while ( i1 <= m )
        temp[t++] = a[i1++];
    while ( i2 <= r )
        temp[t++] = a[i2++];
    for ( int i = l; i <= r; i++ )
        a[i] = temp[i-l];
}

void mergesort0 (int* a, int l, int r, int* buff)
{
    if ( l < r )
    {
        int m = (l + r)/2;
        mergesort0(a, l, m, buff);
        mergesort0(a, m + 1, r, buff);
        merge(a, l, r, buff);
    }
}

void quicksort0 (int* a, int l, int r){
	if (l<r){
		int j = partition(a, l, r);        
		quicksort0(a, l, j-1);
		quicksort0(a, j+1, r);
    }
}

void MergeSort  (int* a, int n)
{
	int* buff = new int[n];
	mergesort0(a, 0, n-1, buff);
	delete[] buff;
}

void InsertSort (int* a, int n){
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

void QuickSort  (int* a, int n){
	quicksort0(a, 0, n-1);
}

void RadixSort  (int* a, int n){
	int bs[10];
	int i, m=abs(a[0]), e=1;
	for (i=1; i<n; i++)
		if (abs(a[i])>m)
			m=abs(a[i]);
	int* b = new int[n];
	while (m/e>0){
		for (i=0; i<10; i++) 
			bs[i]=0;
		for (i=0; i<n; i++) 
			bs[(abs(a[i])/e)%10]++;
		for (i=1; i<10; i++) 
			bs[i]+=bs[i-1];
		for (i = n-1; i >= 0; i--)
			b[--bs[abs(a[i]) / e%10]] = a[i];
		for (i=0; i<n; i++)
			a[i]=b[i];
		e*=10;
	}
	delete[] b;
	splitnegs (a, n);
}

void HeapSort   (int* a, int n){
	THeap h(a,n);
	for (int i=h.GetSize(); i>0; i--){
				swap(a[0], a[i-1]);
				h.DecSize();
				h.Hippefy(0);
			};
}

void Sort(int* a, int n, int i){
	switch (i) {
	case 1:
		MergeSort  (a, n);
		break;
	case 2:
		InsertSort (a, n);
		break;
	case 3:
		QuickSort  (a, n);
		break;
	case 4:
		qsort      (a, n, sizeof(int), comp);
		break;
	case 5:
		RadixSort  (a, n);
		break;
	case 6:
		HeapSort   (a, n);
		break;
	}
}

int main(){
	//freopen("in.txt", "rt", stdin);
	//freopen("out.txt", "wt", stdout);
	int n, ct, t;
	cin >> n;
	int* a = new int[n];
	int* b = new int[n];
	for (int i=0; i<n; i++){
		a[i]=rand();
		b[i]=a[i];
	}
	for (int i=1; i<7; i++){
		ct=clock();
		Sort(a,n,i);
		t=clock()-ct;
		name(i);
		cout << " " << ((float)t)/CLOCKS_PER_SEC) << " sec ";
		state(corr(a,n));
		cout << endl;
		for (int j=0; j<n; j++){
			a[j]=b[j];
		}
	}
}
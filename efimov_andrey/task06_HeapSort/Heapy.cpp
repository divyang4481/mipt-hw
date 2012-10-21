#include <iostream>
using namespace std;


struct THeap{
	private:
		int* buf;
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
		int size;
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
		THeap(){
		};
		THeap(int* arr, int n){
			buf = arr;
			size = n;
			BuildHeap();
		};
		void Print(){
			for (int i=0; i<size; i++)
				cout << buf[i] << " ";
		}
		/*void Insert (int e){
			size++;

		}*/
		//void Delete (int* pe);
		int Max(){
			return buf[0];
		}
		int ExtractMax(){
			int r=buf[0];
			swap(buf[0], buf[size--]);
			Hippefy(0);
		}
		int GetSize(){
			return size;
		}
		const int* GetBuf(){
			return buf;
		}
};

void swap(int* a, int* b){
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

void HeapSort(int* a, int n){
	THeap h(a,n);
	for (int i=h.size; i>0; i--){
				swap(a[0], a[i-1]);
				h.size--;
				h.Hippefy(0);
			};
}

int main(){
	freopen("in.txt", "rt", stdin);
	freopen("out.txt", "wt", stdout);
	const int C=10;
	int A[C];
	for (int i=0; i<C; ++i)
		//A[i]=rand()%100;
		cin >> A[i];
	HeapSort(A, C);
	for (int i=0; i<C; i++)
		cout << A[i] << " ";
	return 0;
}
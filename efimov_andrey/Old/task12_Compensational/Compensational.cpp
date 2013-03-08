#include <iostream>
#include <ctime>

using namespace std;

void debugprint(float* a, int size){
	for (int i=0; i<size; i++){
		cout << a[i] << " ";
	};
	cout << endl;
}

struct TPQueue{
	private:
		float* buf;
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
		void BuildPQ(){
			for (int i=Parent(size-1); i>=0; --i)
				Hippefy(i);
		}
	public:
		void DecSize(){
			size--;
		}
		void IncSize(){
			size++;
		}
		void Hippefy (int ix){
			int min=ix, l=lc(ix), r=rc(ix);
			if ((l<size)&&(buf[ix]>buf[l]))
				min=l;
			if ((r<size)&&(buf[min]>buf[r]))
				min=r;
			if (min!=ix){
				swap(buf[ix],buf[min]);
				Hippefy(min);
			}
		}
		TPQueue(float* arr, int n){
			buf = arr;
			size = n;
			BuildPQ();
		};
		float ExtractMin(){
			float r=buf[0];
			swap(buf[0], buf[size-1]);
			DecSize();
			Hippefy(0);
			return r;
		}
		void Insert(float v){
			int ix=size;
			IncSize();
			buf[ix]=v;
			while (buf[ix]<buf[Parent(ix)]){
				swap(buf[ix], buf[Parent(ix)]);
				ix=Parent(ix);
			}
		}
};

float KahanSum(float* a, int size){
	float sum=0.0, c, t, p=0.0;
	for (int i=0; i<size; i++){
		c=a[i]-p;
		t=sum+c;
		p=(t-sum)-c;
		sum=t;
	}
	return sum;
}

float QueueSum(float* arr, int size){
	float a, b;
	TPQueue h (arr, size);
	for (int i=0; i<size-1; i++){
		a=h.ExtractMin();
		b=h.ExtractMin();
		h.Insert(a+b);
	}
	return arr[0];
}

int main(){
	int n, t;
	cin >> n;
	float* a=new float [n];
	for (int i=0; i<n; i++)
		cin >> a[i];
	t=clock();
	cout << KahanSum(a, n) << " " << ((float)(clock()-t))/CLOCKS_PER_SEC << endl;
	t=clock();
	cout << QueueSum(a, n) << " " << ((float)(clock()-t))/CLOCKS_PER_SEC << endl;
	system("pause");
	delete [] a;
	return 0;
}
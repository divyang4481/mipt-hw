#include <iostream>
#include <vector>

using namespace std;

template <typename T>

class TVector {
public:
	int size;
    int capacity;
	T *buf;
    
	typedef T* iterator;
    typedef const T* const_iterator;
	
	TVector() {
		size = 0;
		capacity = 1;
		buf = new T[capacity];
	}

	~TVector() {
		size = 0;
		capacity = 0;
		delete[] buf;
	}

	int Size() {
		return size;
	}

	bool Empty() const {
        return(size == 0);
    }

	void Clear() {
		size = 0;
	}

	void Swap(TVector &other) { //!!
		swap(*this.buf, other.buf);
		swap(*this.size, other.size);
		swap(*this.buf, other.buf);
	}

	void Resize() {
		capacity *= 2;
		T* buf_new = new T[capacity];
		for (int i = 0; i < size - 1; ++i) {
			buf_new[i] = buf[i];
		}
		delete buf;
		buf = buf_new;

	}

	void Reserve(int n) { 
		while (capacity < n) 
			Resize();	
	}
	
	int Capacity() {
		return(capacity);
	}

	iterator Begin() {
		return(buf);
	}

	iterator End() {
		return(buf + size);
	}

	T& operator[](int n) {
		if (n <= size && n >= 0 )
			return(buf[n]);
		else
			cout << "wrong index" << endl;
	}
	
	T& Front() {
		return(buf[0]);
	}

	T& Back() {
		return(buf[size - 1]);
	}

	void Push_back(T n) {
		size++;
		Reserve(size);
		buf[size - 1] = n;
	}

	void Pop_back() {
		size--;
	}

	void Insert (iterator ind, const T& n) {
		size++;
		Reserve(size);
		for(iterator i = End(); i != ind; --i) {
			*i = *(i - 1);
		}
		*ind = n;
	}

	void Erase(iterator ind) {
		for (iterator i = ind; i != End(); ++i)
			*i = *(i + 1);
		size--;
	} 
	TVector& operator= (TVector& other) /*const?*/ {
		delete[] buf;
		size = other.Size();
		capacity = other.Capacity();
		buf = new T[size];
		for (int i = 0; i < other.Size(); ++i)
			Push_back(other[i]);
		return *this;
    }



};


int main() {
	//freopen("output.txt", "w", stdout);

	TVector<int> V1;

	cout << "Empty? " << V1.Empty() << " Size: " << V1.Size() << " Capacity: " << V1.Capacity() << endl;
	cout << "V1: " << endl;
	for (int i = 0; i < 10; ++i) {
		V1.Push_back(i);
	    cout << V1[i] << endl;
	}
	cout << "Empty? " << V1.Empty() << " Size: " << V1.Size() << " Capacity: " << V1.Capacity() << endl;
	cout << "First element: " << V1.Front() << " Last element: " << V1.Back() << endl;

	////for swap
	//TVector<int> V2;
	//for (int i = 9; i >= 0; --i) {
	//	V2.Push_back(i);
	//}	
	//cout << "V2: " << endl;
	//for (int i = 0; i < 10; ++i) {
	//    cout << V2[i] << endl;
	//}

//	V1.Pop_back();
//	for (int i = 0; i < V1.Size(); ++i) {
//	    cout << V1[i] << endl;
//	}

	V1.Insert(V1.Begin(), 11);
	cout << "V1: " << endl;	
	for (int i = 0; i < V1.Size(); ++i) {
	    cout << V1[i] << endl;
	}

	V1.Erase(V1.Begin());
	cout << "V1: " << endl;	
	for (int i = 0; i < V1.Size(); ++i) {
	    cout << V1[i] << endl;
	}
	

	return 0;
}
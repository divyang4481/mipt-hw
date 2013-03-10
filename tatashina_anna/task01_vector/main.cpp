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

	void Swap(TVector &other) {
		swap(*this.buf, other.buf);
		swap(*this.size, other.size);
		swap(*this.buf, other.buf);
	}

	void Resize() {
		capacity *= 2;
		T* buf_new = new T[capacity];
		for (int i = 0; i < size - 1; ++i) {
			buf_new[i] = buf[i];
			cout << buf_new[i] << " "; 	
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

	T& operator[](size_t n) {
		if (n <= size && n >= 0 )
			return(buf[n])
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
		buf[end] = 0; //проверить
		size--;
	}

	void Insert (iterator ind, const T& n) {
		size++;
		reserve(size);
		for(iterator i = End(); i != ind; --i) {
			buf[i] = buf[i - 1];
		}
		buf[ind] = n;
	}

	void Erase(iterator ind) {
		for (iterator i = ind; i != End(), ++i)
			buf[i] = buf[i + 1];
		size--;
	} 

};


int main() {
	//freopen("output.txt", "w", stdout);
	TVector<int> V1;
	
	for (int i = 0; i < 10; ++i)
		V1.Push_back(i);

	cout << V1.Size() << endl;

	

	return 0;
}
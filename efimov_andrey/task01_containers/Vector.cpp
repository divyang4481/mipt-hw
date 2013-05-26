#include <iostream>
#include <algorithm>
using namespace std;

class A{
public:
	static int creat;
	A(){
		++creat;
	}
	A(A& other){
		++creat;
	}
	~A(){
		--creat;
	}
};

int A::creat = 0;

template <typename T>
class TVector{
	size_t size;
	size_t cap;
	T *buf;
public:
	typedef T* Iterator;
	typedef const T* const_iterator;
	TVector(){
		size = 0;
		cap = 1;
		buf = 0;
	}
	TVector(size_t s){
		size = s;
		cap = s;
		buf = new T[s];
	}
	TVector(const TVector <T> &other){
		this->buf = NULL;
		*this = other;    
	}
	~TVector(){
		size = 0;
		cap = 0;
		delete[] buf;      
	}    
	TVector& operator= (const TVector<T> &other){
		if (this == &other)
			return *this;
		if (this->buf != NULL)
			delete[] buf;
		size = other.getsize();
		cap = other.capacity();
		buf = new T[cap];
		for (size_t i=0; i<size; ++i)
			buf[i] = other[i];
		return *this;
	}
	size_t getsize() const{
		return size;
	}
	size_t capacity() const{
		return cap;
	}
	bool empty() const{
		return size==0;
	}
	void clear(){
		size = 0;
	}
	void reserve(size_t n){
		if (n>cap){
			T* temp = new T[n];
			for (int i=0; i<size; ++i)
				temp[i] = buf[i];
			delete[] buf;
			cap = n;
			buf = temp;
		}
	}
	void resize(size_t n){
		if (n>cap)
			reserve(n);
		size=n;
	}
	void Swap(TVector<T> &other){
		swap(other, *this);	
	}
	void push_back(const T &v){
		if (cap<= size+1){
			reserve(cap*2);
		}
		*end()=v;
		size++;
	}
	void pop_back(){
		if (!empty()) size--;
	}
	Iterator insert (Iterator pos, const T& v){
		insert(pos, 1, v);
		return pos;
	}
	void insert (Iterator pos, size_t n, const T& v){
		T l = pos - begin();
		while (cap<=size+n)
			reserve(cap*2);
		Iterator b = begin();
		for (Iterator i=end()+n-1; i!=b+l+n-1; --i)
			*i=*(i-n);
		for (Iterator i=b+l+n-1; i>=b+l; --i) 
			*i = v;
		size+=n;		
	}
	Iterator erase(Iterator pos){
		for (Iterator i=pos; i!=end(); ++i) *i=*(i+1);
		size--;
		return pos;
	}
	Iterator erase(Iterator first, Iterator last){
		if (last>=end()) last=end()-1;
		for (Iterator i = first; i<=last; ++i) *i=*(last-first+i+1);
		size = size - ((int)(last-first)+1);
		return first;	
	}
	T& operator[] (size_t n){
		if (n>=0 && n<=size)
			return buf[n];
	}
	const T& operator[] (size_t n) const{
		if (n>=0 && n<=size)
			return buf[n];
	}
	Iterator begin(){
		return buf; 
	}
	Iterator end(){   
		return buf+size;
	}
	const_iterator begin() const{
		return buf;
	}
	const_iterator end() const{
		return buf+size;
	}
	T& front(){
		return *buf;
	}
	const T& front() const{
		return *buf;
	}
	T& back(){
		return *(buf+size-1);
	}
	const T& back() const{
		return *(buf+size-1);
	}
};

template <typename T>
void print(TVector<T> v){
	for(TVector<int>::Iterator it=v.begin(); it!=v.end(); ++it)
		cout << ' ' << *it;
	cout << endl;
};

void Its2amAndImJustSittingHereTesturbating(){
	TVector<int> a;
	TVector<int> b;
	for (int i=0; i<20; ++i){
		a.push_back(i);
		b.push_back(20-i);
	}
	cout << "a: ";
	print(a);
	cout << "b: ";
	print(b);
	cout << "Popback for both" << endl;
	a.pop_back();
	cout << "a: ";
	print(a);
	cout << "b: ";
	print(b);
	cout << "Swhap" << endl;
	a.Swap(b);
	cout << "a: ";
	print(a);
	cout << "b: ";
	print(b);
	cout << "INSERTIONNN" << endl;
	a.insert(a.begin()+2, 9);
	b.insert(b.begin()+2, 0);
	cout << "a: ";
	print(a);
	cout << "b: ";
	print(b);
	cout << "More insertion!" << endl;
	a.insert(a.begin(), 3, 4);
	cout << "a: ";
	print(a);
	cout << "b: ";
	print(b);
	cout << "Destroy the lesser middle nodes!" << endl;
	a.erase(a.begin()+7);
	b.erase(b.begin()+6, b.begin()+8);
	cout << "a: ";
	print(a);
	cout << "b: ";
	print(b);
	system("pause");
};

void TestDriveUnlimited(){
	{
		TVector<A> uber;
		uber.resize(18);
		uber.push_back(A());
		uber.reserve(32);
		uber.resize(4);
		uber.pop_back();
		uber.clear();
	}
	cout << A::creat; // if this here is zero, everything's fine
	system("pause");
}

int main(){
	Its2amAndImJustSittingHereTesturbating();
	TestDriveUnlimited();
	return 0;
}

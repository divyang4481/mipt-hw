// vector.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <vector>
using namespace std;
template <typename T>
class TVector
{
private:
	T* Buf;
	size_t Capacity;
	size_t Size;
	friend void PrintVector(const TVector& a);
public:
	static int Created;
    static int Deleted;
	typedef T* iterator;
	typedef const T* const_iterator;
	// constructors, destructor, operator=
	TVector()
	{
		Size = 0;
		Capacity = 1;
		Buf = new T[Capacity];
		++Created;
	}
	TVector(size_t s)
	{
		Size = s;
		Capacity = s;
		Buf = new T[Capacity];
		++Created;
	}
	~TVector()
	{
		Size = 0;
		Capacity = 0;
		delete [] Buf;
		++Deleted;
	}
	TVector& operator = (TVector& a)
	{
		delete [] Buf;
		Size = a.size();
		Capacity = a.capacity();
		Buf = new T[Size];
		for (unsigned int i = 0; i < a.size(); i++)
			Buf[i] =a[i];
		return *this;
	}
	//element access
	T& operator [] (size_t n)
	{
		if ((n>=0) && (n<Size))
			return Buf[n];
	}
	const T& operator [] (size_t n) const
	{
		if (n>=0) && (n<Size)
			return Buf[n];
	}
	T& front()
	{
		return Buf[0];
	}
	T& back()
	{
		return Buf[Size-1];
	}
	//iterators
	iterator begin()
	{
		return Buf;
	}
	const_iterator begin() const
	{
		return Buf;
	}
	iterator end()
	{
		return (Buf + Size);
	}
	const_iterator end() const
	{
	    return (Buf + Size)
	}
	//capacity
	size_t size()
	{
		return Size;
	}
	size_t capacity()
	{
		return Capacity;
	}
	void reserve(size_t n)
	{
		if (n > Capacity)
		{
			T* help = new T[n];
			for (unsigned int i = 0; i < Size; ++i)
				help[i] = Buf[i];
			Capacity = n;
			Buf = help;
		}
	}
	void resize(size_t n)
	{
		if (n > Capacity)
			Reserve(n);
		Size = n;
	}
	bool empty()const
	{
		return Size == 0;
	}
	//modifiers
	void swap(TVector &a)
	{
		TVector help;
		help = *this;
		*this = a;
		a = help;
	}
	void clear()
	{
		Size = 0;
	}
	void pop_back()
	{
		if (!empty()) --Size;
	}
	void push_back(T key)
	{
		if (Size  == Capacity)
			reserve( Capacity << 1);
		*end() = key;
		++Size;
	}
	iterator insert(iterator position, T key)
	{
		insert(position, 1, key);
		return position;
	}
	void insert(iterator position, size_t n, T key)
	{
		for (;Capacity <= (Size + n); reserve(Capacity << 1));
		for (iterator i = end() + n - 1; 
			i != position + n - 1; --i) *i = *(i - n);
		for (iterator i = position + n - 1; i >= position; --i)
			*i = key;
		Size += n;
	}
	iterator erase(iterator position)
	{
		for (iterator i = position; i != end(); ++i) *i = *(i+1);
		--Size;
		return position;
	}
	iterator erase(iterator first, iterator last)
	{
		for (iterator i = first; i < end() - (int)(last-first); ++i) 
			*i = *(i + (int)(last - first)+1);
		Size -= (int)(last - first) + 1;
		return first;
	}
    void printvector()
	{
		cout<<"Size: "<< Size << '\n';
		for (int i = 0; i < Size; ++i)
			cout << Buf[i] << ' ';
		cout << '\n';
	}
    

};

int TVector<int>:: Created=0;
int TVector<int>:: Deleted=0;

int _tmain(int argc, _TCHAR* argv[])
{
	{TVector<int> v,v1;
	for (int i = 0; i < 20; ++i)
	{
	   v.push_back(i);
	   v1.push_back(19 - i);
	}
	v.printvector();
	v.insert(v.begin(), 2, 200);
	v.insert(v.end(), 2, 300);
	v.printvector();
	v1.printvector();
	v.erase(v.begin(), v.begin());
	v.printvector();
	v.swap(v1);
	v.printvector();
	v1.printvector();
	v1.erase(v1.begin(), v1.begin()+1);
	cout << *v1.begin() << '\n';
	v1.printvector();}
	cout << TVector<int>::Created << '\n' << TVector<int>::Deleted << '\n';
	return 0;
}


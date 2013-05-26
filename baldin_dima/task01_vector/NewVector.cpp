#include <iostream>
#include <vector>
using namespace std;
template <typename T>
class TVector
{
	T* Buf;
	size_t Size;
	size_t Capacity;
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	iterator begin()
	{
		return Buf;
	}
	iterator end()
	{
		return (Buf + Size);
	}
	const_iterator begin() const
	{
		return Buf;
	}
	const_iterator end() const
	{
		return (Buf +Size);
	}
	TVector()
	{
		Size = 0;
		Capacity = 1;
		Buf = new T[1];
	}
	TVector (TVector& a)
	{
		Size = 0;
		Capacity = 1;
		Buf = new T[1];
		*this = a;
		

	}
	~TVector()
	{
		delete [] Buf;
	}
	size_t size()
	{
		return Size;
	}
	bool empty() const
	{
		return (Size == 0);
	}
	void clear()
	{
		Size = 0;
	}
	TVector swap(TVector &a)
	{
		swap(Size, a.Size);
		swap(Capacity, a.Capacity);
		swap(Buf, a.Buf);
	}
	void push_back(const T& a)
	{
		if (Capacity <= Size) reserve(Capacity + 1);
		Buf[Size] = a;
		++Size;
		
	}
	void resize( size_t n)
	{
		if (n > Capacity) reserve(n);
		Size = n;
	}
	void reserve (size_t n)
	{
		if (Capacity == 0) ++Capacity;
		for (;Capacity < n; Capacity *= 2);
		T* Help = new T [Capacity];
		for (size_t i = 0; i < Size; ++i)
			Help[i] = Buf[i];
		delete[] Buf;
		Buf = Help;

	}
	const T& operator [] (int n) const
	{
		return Buf[n];
	}
	T& operator [] (int n)
	{
		return Buf[n];
	}
	TVector& operator=(const TVector& a)
	{
		clear();
		for (const_iterator it = a.begin(); it < a.end(); ++it)
			push_back(*it);
		return *this;
	}
	size_t capacity() const
	{
		return Capacity;
	}
	
	T& front() 
	{
		return Buf[0];
	}
	T& back()
	{
		return Buf[Size - 1];
	}
	const T& front() const
	{
		return Buf[0];
	}
	const T& back() const
	{
		return Buf[Size - 1];
	}
	void pop_back()
	{
		--Size;
	}
	iterator insert(iterator in, const T& a)
	{
		if (Capacity == Size) reserve(Size + 1);
		for (iterator it = end(); it > in; --it)
			*it = *(it - 1);
		*in = a;
		++Size;
		return in;
	}
	iterator erase(iterator in)
	{
		for (;in < (end() - 1); ++in)
			*in = *(in+1);
		Size--;
		return in;
	}
};
template <typename T>
void print(TVector<T> a)
	{
		for (typename TVector<T>::const_iterator it = a.begin(); it < a.end(); ++it)
			cout << *it << ' ' ;
		cout << endl;
	}
struct myint
{
        size_t x;
        static int Created;
        static int Deleted;
        myint()
        {
                ++Created;
                x = 0;
        }
        myint(const myint &a)
        {
                ++Created;
                x = a.x;
        }
        ~myint()
        {
                ++Deleted;
        
        }
                myint operator+(myint a)
                {
                        myint b;
                        b.x = a.x + x ;
                        return b;
                }
                myint& operator+=(myint a)
                {
                        x += a.x;
                        return *this;
                }
};
int myint::Created = 0;
int myint::Deleted = 0;
int main()
{
	cout << "Create vector a" << endl;
	TVector<int> a;
	cout << "Fill in values from 0 to 14" << endl;
	for (int i = 0; i < 15; ++i)
		a.push_back(i);
	cout << "a: " ;
	print(a);
	cout << "TVector b(a)" << endl;
	TVector<int> b(a);
	cout << "b: " ;
	print(b);
	cout << "b.erase(b.begin() + 3)" << endl;
	b.erase(b.begin()+3);
	cout << "b: ";
	print(b);
	cout << "b.insert(b.begin() + 3)" << endl;
	b.insert(b.begin()+3, 3);
	cout << "b: ";
	print(b);
	{
		TVector<myint> c;
		myint x;
		for (int i = 0; i < 20; ++i)
		{
			x.x = 0;
			c.push_back(x);
		}
		TVector<myint> d(c);
	}

        {
            TVector<myint> a;
            for (int i = 0; i < 10; ++i)
                a.push_back(myint());

            TVector<myint> b = a;
            for (int i = 0; i < 10; ++i)
                b.push_back(myint());

            a.swap(b);
        }

	cout << "Check memory" << endl;
	cout << myint::Created << ' ' << myint::Deleted << endl;
	return 0;
}

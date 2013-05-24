#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
struct TFoo 
{
    T Value;
    TFoo() : Value(T(0)) { ++Created; }
	TFoo(T v): Value(v) { ++Created; }
    TFoo(const TFoo &other) : Value(other.Value) { ++Created; }
    ~TFoo() { ++Deleted; }
    bool operator< (const TFoo& other) const
    {
        return Value < other.Value;
    }
    TFoo& operator= (const TFoo& other)
    {
        Value = other.Value;
		return *this;
    }
    TFoo& operator= (T r) 
    {
        Value = r;
		return *this;
    }
	void operator += (const TFoo &other)
	{
		Value += other.Value;
	}
	void operator -= (const TFoo &other)
	{
		Value -= other.Value;
	}
	void operator *= (const TFoo &other)
	{
		Value *= other.Value;
	}
	TFoo operator+ (const TFoo &other) const
	{
		TFoo temp(*this);
		temp+=other;
		return temp;
	}
	TFoo operator- (const TFoo &other) const
	{
		TFoo temp(*this);
		temp-=other;
		return temp;
	}
	TFoo operator*(const TFoo &other) const
	{
		TFoo temp(*this);
		temp *= other;
		return temp;
	}
	TFoo operator* (T v) const
	{
		TFoo temp(*this);
		temp.Value*=v;
		return temp;
	}
	bool operator== (const TFoo &a) const
	{
		return (Value == a.Value);
	}
	static int Created;
    static int Deleted;
    static void PrintStats() 
	{
        cout << "TFoo::Created = " << Created << endl << "TFoo::Deleted = " << Deleted << endl;
    }
};

template<> int TFoo<int>::Created = 0;
template<> int TFoo<int>::Deleted = 0;


template <typename T>
class TVector
{
    size_t size;
    size_t cap;
    T *buf;
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    TVector()
    {
        size = 0;
        cap = 1;
        buf = 0;
    }
    TVector(size_t s)
    {
        size = s;
        cap = s;
        buf = new T [s];
    }
    TVector(const TVector <T> &other)
    {
        this->buf = NULL;
        *this = other;
    }
    ~TVector()
    {
        size = 0;
        cap = 0;
        delete [] buf;      
	}    
	TVector& operator = (const TVector<T> &other)
    {
    	if (this == &other)
    		return *this;
    	if (this->buf != NULL)
        	delete [] buf;
        size = other.Size();
        cap = other.Capacity();
        buf = new T[cap];
        for (size_t i=0; i<size; ++i)
        	buf[i] = other[i];
        return *this;
    }
    size_t Size() const
    {
        return size;
    }
    size_t Capacity() const
    {
        return cap;
    }
    bool Empty() const
    {
        return size==0;
    }
    void Clear()
    {
        size = 0;
    }
    void Reserve(size_t n)
    {
        if (n>cap)
        {
            T* temp = new T[n];
            for (size_t i=0; i<size; ++i)
            	temp[i] = buf[i];
            delete [] buf;
            cap = n;
            buf = temp;
        }
    }
    void Resize(size_t n)
    {
        if (n>cap)
            Reserve(n);
        size=n;
    }
    void Swap(TVector <T> &other)
    {
		swap(cap, other.cap);
		swap(size, other.size);
		swap(buf, other.buf);
    }
    void Push_back(const T &v)
    {
        if (cap <= size+1)
        {
            Reserve(cap*2);
        }
        *end()=v;
        size++;
    }
	void Pop_back()
	{
		if (!Empty()) size--;
	}
	iterator Insert (iterator pos, const T& v)
	{
		Insert(pos, 1, v);
		return pos;
	}
	void Insert (iterator pos, size_t n, const T& v)
	{
		T l = pos - begin();
        while (cap <= size+n)
            Reserve(cap*2);
        iterator b = begin();
		for (iterator i=end()+n-1; i!=b+l+n-1; --i)
			*i=*(i-n);
		for (iterator i=b+l+n-1; i>=b+l; --i) 
			*i = v;
		size+=n;		
	}
	iterator Erase (iterator pos)
	{
		for (iterator i=pos; i!=end(); ++i) *i=*(i+1);
		size--;
		return pos;
	}
	iterator Erase (iterator first, iterator last)
	{
		if (last>=end()) last=end()-1;
		for (iterator i = first; i<=last; ++i) *i=*(last-first+i+1);
		size = size - ((int)(last-first)+1);
		return first;	
	}
    T& operator [] (size_t n)
    {
		return buf[n];
    }
    const T& operator [] (size_t n) const
    {
		return buf[n];
    }

    iterator begin()
    {
        return buf; 
    }
    iterator end()
    {   
        return buf+size;
    }
    const_iterator begin() const
    {
        return buf;
    }
    const_iterator end() const
    {
        return buf+size;
    }
	T& front()
	{
		return *buf;
	}
	const T& front() const
	{
		return *buf;
	}
	T& back()
	{
		return *(buf+size-1);
	}
	const T& back() const
	{
		return *(buf+size-1);
	}
};

int main()
{
    TVector <int> v(2);
    v[0]=0;
    *(v.begin()+1)=1;
	cout<<"TVector <int> v(2): ";
    for(TVector <int>::iterator it=v.begin(); it!=v.end(); ++it) cout <<' '<<*it;
    cout<<endl;
    TVector <int> f(v);
    v.Reserve(5);
	cout<<"TVector <int> f(v): ";
    for(TVector <int>::iterator it=f.begin(); it!=f.end(); ++it) cout <<' '<<*it;
    cout<<endl;
    f.Push_back(2);  
    f.Swap(v);
	cout<<"f.Push_back(2), f.Swap(v):"<<endl;
	cout<<"v:";
    for(TVector <int>::iterator it=v.begin(); it!=v.end(); ++it) cout <<' '<<*it;  
    cout<<endl;
	cout<<"f:";
    for(TVector <int>::iterator it=f.begin(); it!=f.end(); ++it) cout <<' '<<*it;
    cout<<endl;
    for (int i=3; i<10; ++i) v.Push_back(i);
	cout<<"Push_back:"<<endl;
    for(TVector <int>::iterator it=v.begin(); it!=v.end(); ++it) cout <<' '<<*it;  
    cout<<endl;
	v.Resize(5);
	cout<<"v.Resize(5):"<<endl;
    for(TVector <int>::iterator it=v.begin(); it!=v.end(); ++it) cout <<' '<<*it;  
    cout<<endl;
	v.Pop_back();
	cout<<"v.Pop_back():"<<endl;
    for(TVector <int>::iterator it=v.begin(); it!=v.end(); ++it) cout <<' '<<*it;  
    cout<<endl;
	TVector <int>::iterator i=v.begin()+2;
	i = v.Insert(i, 55);
	cout<<"v.Insert(v.begin()+2, 55):"<<endl;
    for(TVector <int>::iterator it=v.begin(); it!=v.end(); ++it) cout <<' '<<*it;  
    cout<<endl;
	v.Insert(v.begin()+2, 7, 10);
	cout<<"v.Insert(v.begin()+2, 7, 10):"<<endl;
    for(TVector <int>::iterator it=v.begin(); it!=v.end(); ++it) cout <<' '<<*it;  
    cout<<endl;
	v.Erase(v.begin()+2);
	cout<<"v.Erase(v.begin()+2):"<<endl;
    for(TVector <int>::iterator it=v.begin(); it!=v.end(); ++it) cout <<' '<<*it;  
    cout<<endl;
	v.Erase(v.begin()+3,v.begin()+5);
	cout<<"v.Erase(v.begin()+3,v.begin()+5):"<<endl;
    for(TVector <int>::iterator it=v.begin(); it!=v.end(); ++it) cout <<' '<<*it;  
    cout<<endl;
	cout<<"v.front(): "<<v.front()<<endl<<"v.back(): "<<v.back()<<endl;
	v.Clear();
	cout<<"v.Clear:"<<endl;
	cout << "Memory test" << endl;
	{
		TVector<TFoo<int> > a;
		a.Resize(5);
		a.Reserve(100);
		a.Resize(1);
	}
	TFoo<int>::PrintStats();
    return 0;
}
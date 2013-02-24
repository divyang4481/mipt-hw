#include <iostream>
using namespace std;

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
    TVector(const TVector &other)
    {
        size = other.Size();
        cap = other.Capacity();
        buf = new T[size];
        memcpy(buf, other.cbegin(), sizeof(T)*size);
    }
    ~TVector()
    {
        size = 0;
        cap = 0;
        delete [] buf;
	}
    size_t Size()
    {
        return size;
    }
    size_t Size() const
    {
        return size;
    }
    size_t Capacity()
    {
        return cap;
    }
    size_t Capacity() const
    {
        return cap;
    }
    bool Empty()
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
            memcpy(temp, buf, sizeof(T)*size);
            delete [] buf;
            cap = n;
            buf = temp;
        }
    }
    void Resize(size_t n)
    {
        if (n>cap)
        {
            Reserve(n);
        }
        size=n;
    }
    void Swap(TVector &other)
    {
        TVector <T> *temp = new TVector <T>(*this);
        *temp = other;
        other = *this;
        *this = *temp;
        temp->~TVector();
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
        while (cap <= size+n)
        {
            Reserve(cap*2);
        }
		for (iterator i=end()+n-1; i!=pos+n-1; --i) *i=*(i-n);
		for (iterator i=pos+n-1; i>=pos; --i) *i = v;
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
        if (n>=0 && n<=size)
            return buf[n];
    }
    const T& operator [] (size_t n) const
    {
        if (n>=0 && n<=size)
            return buf[n];
    }
    TVector& operator = (const TVector& other)
    {
        delete [] buf;
        size = other.Size();
        cap = other.Capacity();
        buf = new T[size];
        memcpy(buf, other.cbegin(), sizeof(T)*size);
        return *this;
    }
    iterator begin()
    {
        return buf; 
    }
    iterator end()
    {   
        return buf+size;
    }
    const_iterator cbegin() const
    {
        return buf;
    }
    const_iterator cend() const
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
	cout<<"TVector <int> v(2):";
    for(TVector <int>::iterator it=v.begin(); it!=v.end(); ++it) cout <<' '<<*it;
    cout<<endl;
    TVector <int> f(v);
    v.Reserve(5);
	cout<<"TVector <int> f(v):"<<endl;
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
	v.Insert(v.begin()+1, 5, 2);
	cout<<"v.Insert(v.begin()+1, 5, 2):"<<endl;
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
    for(TVector <int>::iterator it=v.begin(); it!=v.end(); ++it) cout <<' '<<*it;  
    return 0;
}
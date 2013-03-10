#include<iostream>
using namespace std;

template<typename T>
class TVector
{
public:
	T *mas;
	typedef T* iterator;
    typedef const T* const_iterator;
	long Size,rSize;
	TVector();
	~TVector();
	int size();
	bool emty();
	void clear();
	void swap(TVector<T>&);
	void resize(long,T);
	int capacity();
	void reserve(long);
	iterator begin()
	{
		return mas;
	};
	iterator end()
	{
		return mas+Size;
	};
	T operator [](long a)
	{
		return mas[a];
	};
	T back()
	{
		return mas[Size-1];
	};
	T front()
	{
		return mas[0];
	};
	void push_back(T a)
	{
		if(Size==rSize)
		{
			this->reserve(2*rSize+1);
		}
		mas[Size]=a;
		++Size;
	};
	T pop_back()
	{
		if(Size)
		{
		--Size;
		return mas[Size];
		}
	};
	iterator insert(iterator pop,T val)
	{ 
		T kk=*(end()-1);
		int k=0;
		iterator a=end()-1;
		while(a!=pop)
		{
			*a=*(a-1);
			--a;
			++k;
		}
		*a=val;
		k=Size-k;
		push_back(kk);
		return &mas[k-1];
	};
	iterator erase(iterator f,iterator l)
	{
		int k=0,kk=0;
		iterator u=f;
		while(u!=l)
		{
			++u;++kk;
		}
		u=f;
		while(l+k+1!=end())
		{
			*(f+k)=*(l+k+1);
			++k;
		}
		Size-=kk+1;
		return u;
	};
	iterator erase(iterator a)
	{
		iterator u=erase(a,a);
		return u;
	};
	TVector<T>& operator=(TVector<T> &a)
	{
		reserve(a.rSize);
		rSize=a.rSize;
		Size=a.Size;
		for(int i=0;i<Size;++i)mas[i]=a.mas[i];
		return *this;
	};
};

template<typename T>
TVector<T>::TVector()
{
	mas=new T[10];
	Size=0;
	rSize=10;
}

template<typename T>
TVector<T>::~TVector()
{
	delete[] mas;
}

template<typename T>
int TVector<T>::size()
{
	return Size;
}

template<typename T>
bool TVector<T>::emty()
{
	if(Size) return 0;
	else return 1;
}

template<typename T>
void TVector<T>::clear()
{
	Size=0;
}

template<typename T>
void TVector<T>::swap(TVector<T> &v)
{
	TVector<T> a;
	a=*this;
	*this=v;
	v=a;

}

template<typename T>
void TVector<T>::resize(long n,T v)
{
	if(n<rSize)
	{
		for(int i=Size;i<n;++i)mas[i]=v;
		Size=n;
	}
	else
	{
		T *a=new T[n];
		for(int i=0;i<Size;++i)a[i]=mas[i];
		for(int i=Size;i<n;++i)a[i]=v;
		delete[] mas;
		mas=a;
		Size=rSize=n;
	}
}

template<typename T>
int TVector<T>::capacity()
{
	return rSize;
}

template<typename T>
void TVector<T>::reserve(long n)
{
	if(n>rSize)
	{
		T *a=new T[n];
		for(int i=0;i<Size;++i)a[i]=mas[i];
		delete[] mas;
		mas=a;
		rSize=n;
	}
}

int main()
{
	TVector<char> a,b;
	TVector<char>::iterator u;
	a.push_back('h');
	a.push_back('e');
	a.push_back('l');
	a.push_back('l');
	a.push_back('o');
	u=a.begin();
	while(u!=a.end()){cout<<*u;++u;}
	cout<<"   Here "<<a.size()<<"words\n";
	cout<<"real size of vector-"<<a.capacity();
	if(a.emty())cout<<"\nvector are clear";
	a.clear();
	if(a.emty())cout<<"\nvector are clear\n";
	a.push_back('1');
	b.push_back('2');
	a.swap(b);
	u=a.begin();
	while(u!=a.end()){cout<<*u;++u;}
	u=b.begin();
	while(u!=b.end()){cout<<*u;++u;}
	a.resize(30,'o');
	cout<<a.size()<<"\n";
	cout<<a[0]<<a[1]<<a.back()<<a.front();
	for(int i=0;i<10;++i)
		a.pop_back();
	cout<<a.size()<<" "<<a.capacity();
	a.insert(a.begin()+5,'e');
	cout<<a[0];
	a.erase(a.begin()+2,a.end()-2);
	u=a.begin();
	cout<<'\n';
	while(u!=a.end()){cout<<*u;++u;}
	return 0;
}
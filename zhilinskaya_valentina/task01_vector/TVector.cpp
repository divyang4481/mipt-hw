# include <iostream>
# include <stdlib.h>

using namespace std;

struct leak {
	static int Created;
	static int Deleted;
	leak() {++Created;}
	leak (const leak&) {++Created;}
	~leak() {++Deleted;}
};
int leak :: Created = 0;
int leak :: Deleted = 0;
template <class T>
class TVector
{
private:
	int _size;
    int _capacity;
    T* _array;
public:


	typedef T* iterator;
    typedef const T* const_iterator;
    TVector()
    {
		_size = 0;
		_capacity = 1;
		_array=new T[_capacity];
    }
    TVector (const TVector<T>& array2)
    {
        _capacity=array2.capacity();
        _size=array2.size();
        _array=new T[_capacity];
        for(int i=0; i<_size; ++i)
            _array[i]=array2[i];
    }

    TVector (const T &a, int N=0)
    {
        _size=N;
        _capacity=N;
        _array=new T[N];
        for(int i=0; i<_size; ++i)
            _array[i]=a;
    }


    ~TVector ()
    {
        delete[] _array;
    }
    int size () const
    {
        return _size;
    }
    bool empty () const
    {
        return _size == 0;
    }
    void clear ()
    {
        delete[] _array;
        _array=new T[0];
        _size=0;
        _capacity=0;
    }
    void swap (TVector<T>& array2)
    {
        std::swap(_size, array2._size);
        std::swap(_capacity, array2._capacity);
        std::swap(_array, array2._array);
    }
    void resize (int another_size, T a=T())//расширить до Another_size и заполнить a
    {
             if (another_size<_size)
             {
                    if (another_size<(_capacity/2))
                    {
                        T* another_array = new T[another_size*2];
                        for (int i=0; i<another_size; ++i)
                            another_array[i]=_array[i];

                    delete[] _array;
                    _array=another_array;
                    _capacity=another_size*2;
                    }
             }
      if (another_size>_size){
          if(another_size>_capacity){
             _capacity=another_size*2;
             T* another_array = new T[_capacity];
             for (int i=0; i<_size; ++i){another_array[i]=_array[i];}
             delete[] _array;
             _array=another_array;
          }
          for (int i=_size;i<another_size;++i){_array[i]=a;}
      }
      _size=another_size;
    }



    int capacity () const
    {
        return _capacity;
    }
    void reserve (int N)
    {
         if(N>_capacity)
         {
            _capacity=N;
            T* array2=new T[N];
            for(int i=0; i<_size; ++i)
                array2[i]=_array[i];

            delete[] _array;
            _array=array2;
         }

    }
    iterator begin()
    {
        if(_size==0)
        {
                iterator iter(NULL);
                return iter;
        }
        iterator iter(&_array[0]);
        return iter;
    }
    iterator end()
    {
        if (_size==0)
        {
            iterator iter(NULL);
            return iter;
        }
        iterator iter(&_array[0]+_size);
        return iter;
    }
	iterator begin() const
    {
        if(_size==0)
        {
                iterator iter(NULL);
                return iter;
        }
        iterator iter(&_array[0]);
        return iter;
    }
    iterator end() const
    {
        if (_size==0)
        {
            iterator iter(NULL);
            return iter;
        }
        iterator iter(&_array[0]+_size);
        return iter;
    }
    T& operator[](int i)
    {
        if(_size>i)
            return _array[i];
        else return _array[0];
    }
    const T& operator[](int i) const
    {
        if(_size>i)
            return _array[i];
        else return _array[0];
    }
    T& back ()
    {
        return ((_size == 0)?_array[0]:_array[_size-1]); // должна быть вторая версия бэк - const T& back() const
    }
    T& front ()
    {
        return _array[0];
    }
	T& back () const
    {
        return ((_size == 0)?_array[0]:_array[_size-1]); // должна быть вторая версия бэк - const T& back() const
    }
    T& front () const
    {
        return _array[0];
    }

    void push_back (const T& a)
    {
             if (_capacity>=_size+1)
             {
                    _array[_size]=a;
                    _size++;
            }
            else
            {
                if (_capacity>0)
                    _capacity*=2;
                else
                    _capacity=1;

                T* another_array = new T[_capacity];
                for (int i=0; i<_size; ++i)
                    another_array[i]=_array[i];
                delete[] _array;
                _array=another_array;

                _array[_size]=a;
                _size++;
            }

    }
    void pop_back()
    {
        if (_size>0)
        {
                _size--;

                if (_capacity> _size*2)
            {
                _capacity/=2;
                T* another_array = new T[_capacity];
                for (int i=0; i<_size; ++i){another_array[i]=_array[i];}
                delete[] _array;
                _array=another_array;
            }
        }
    }

	void insert (iterator iter, const T& n) {
		_size++;
		reserve(_size);
		for(iterator i = end(); i != iter; --i) {
			*i = *(i - 1);
		}
		*iter = n;
	}

	void erase(iterator iter) {
		for (iterator i = iter; i != end(); ++i)
			*i = *(i + 1);
		_size--;
	} 
    TVector<T>& operator = (const TVector<T>& TvArray2)
    {
		delete[] _array;
        _size=TvArray2.size();
        _capacity=TvArray2.capacity();
		_array = new T[_capacity];
		for (int i = 0; i < TvArray2.size(); ++i)
			_array[i] = TvArray2[i];
		return *this;
    }
};


static void Test() {
    TVector<leak> a;
    for (int i = 0; i < 10; ++i)
        a.push_back(leak());

    TVector<leak> b = a;
    for (int i = 0; i < 10; ++i)
        b.push_back(leak());

    a.swap(b);

    TVector<leak> c;
    a = c;

    const TVector<leak> d(a);
    const leak& lk = d.front();
}

int main()
{
/*    TVector<int> array1;
    array1.push_back(2);		//2 
    array1.push_back(4);		//24 
    array1.push_back(3);		//243 
	for (int i = 0; i<array1.size(); ++i)
    for (int i = 0; i<array1.size(); ++i) cout<<array1[i]<<" ";
	cout << '\n';
	array1.pop_back();	//24 
	for (int i = 0; i<array1.size(); ++i) cout<<array1[i]<<" ";
	cout << '\n';
	cout << "empty? " << array1.empty() <<'\n';
	array1.resize(10,0);
	array1.resize(7,8);
	array1.reserve(20);
	cout << array1.size() <<' '<<array1.capacity() << '\n';
	array1.reserve(4);
	cout << array1.size() <<' '<<array1.capacity() << '\n';
	for (int i = 0; i<array1.size(); ++i) cout<<array1[i]<<" ";

	TVector<int> array2;
	array2.push_back(100);
	array1.swap(array2);
	cout<<'\n';
	for (int i = 0; i<array1.size(); ++i) cout<<array1[i]<<" ";
	cout <<"\n size = "<< array1.size()<<" capacity = "<<array1.capacity()<<'\n';
	cout<<'\n';
	for (int i = 0; i<array2.size(); ++i) cout<<array2[i]<<" ";
	cout <<"\n array2.front() = "<< array2.front() << "  array2.back() = "<< array2.back()<<"  array2[1] = " << array2[1] << '\n';
	array1 = array2;
	cout << "\n first \n";
	for (int i = 0; i<array1.size(); ++i) cout<<array1[i]<<" ";
	cout << "\n second\n";
	for (int i = 0; i<array2.size(); ++i) cout<<array2[i]<<" ";

	array1.insert(array1.begin(),123);
	array2.erase(array2.begin());
	cout << "\n first \n";
	for (int i = 0; i<array1.size(); ++i) cout<<array1[i]<<" ";
	cout << "\n second\n";
	for (int i = 0; i<array2.size(); ++i) cout<<array2[i]<<" ";*/
	//---------------------------------------------------------------------------------------------------------LEAK
        /*
	{	
		cout << "\n push_back + def.constr.";
		TVector<leak> array3;
		leak z;
		for (int i = 0; i< 5; ++i)
			array3.push_back(z);
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{	
		cout << "\n push_back + pop_back + def.constr.";
		TVector<leak> array3;
		leak z;
		for (int i = 0; i< 10; ++i)
			array3.push_back(z);
		for (int i = 0; i< 6; ++i)
			array3.pop_back();
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{	
		cout << "\n constr. + size + empty + capacity + back + front + [] + end + begin (dont change (except constr.))";
		leak z;
		TVector<leak> array3(z, 12);
		array3.size();
		array3.capacity();
		array3.empty();
		z = array3.back();
		z = array3.front();
		z = array3[2];
		array3.end(); array3.begin();
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{
		cout << "\n constr.cop. + swap";
		leak z;
		TVector<leak> array3(z, 5);
		TVector<leak> array4(array3);
		array3.swap(array4);
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{
		cout << "\n constr. + clear";
		leak z;
		TVector<leak> array3(z, 5);
		array3.clear();
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{
		cout << "\n constr. + resize";
		leak z;
		TVector<leak> array3(z, 5);
		array3.resize(19);
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{
		cout << "\n constr. + reserve";
		leak z;
		TVector<leak> array3(z, 5);
		array3.reserve(15);
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{
		cout << "\n constr. + insert";
		leak z;
		TVector<leak> array3(z, 5);
		array3.insert(array3.begin(), z);
		array3.insert(array3.begin(), z);
		array3.insert(array3.begin(), z);
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{
		cout << "\n constr. + erase";
		leak z;
		TVector<leak> array3(z, 20);
		array3.erase(array3.begin());
		array3.erase(array3.begin());
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{
		cout << "\n constr. + op=";
		leak z;
		TVector<leak> array3(z, 5);
		TVector<leak> array4(z, 9);
		array4 = array3;
	}
        */
        Test();
        cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	system("pause");
	return 0;
}

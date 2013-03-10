# include <iostream>
# include <stdlib.h>

using namespace std;

template <class T>
class TVector
{
private:
    size_t _size;//вектор
    size_t _capacity;//буфер
    T* _array;
public:
    class TIterator
    {

    private:
        T* _pt;
    public:
        TIterator(T* a = 0)
        {
            _pt = a;
        }

        TIterator operator ++ (int)
        {
            TIterator a;
            a._pt=_pt;
            _pt++;
            return a;
        }
        TIterator operator -- (int)
        {
            TIterator a;
            a._pt=_pt;
            _pt--;
            return a;
        }
                TIterator& operator ++ ()
        {
            _pt++;
            return *this;
        }

        TIterator& operator -- ()
        {
            _pt--;
            return *this;
        }


        bool operator == (TIterator a) const
        {
            return (_pt==a._pt);
        }
        bool operator != (TIterator a) const
        {
            return (_pt!=a._pt);
        }
        void operator += (size_t a)

        {
            _pt=_pt+a;
        }
        void operator -= (size_t a)
        {
            _pt=_pt-a;
        }
        TIterator& operator = (const TIterator& a)
        {
            return (_pt=a._pt);
        }
        bool operator < (TIterator a) const
        {
            return (_pt<a._pt);
        }
        bool operator > (TIterator a) const
        {
            return (_pt>a._pt);
        }

        T& operator * ()
        {
            return *_pt;
        }
        T& operator [](size_t i)
        {
            return *(_pt+i);
        }
         T& operator->() const
        {
            return &(operator*());
        }

    };

    class TIterator_const
    {
    private:
        T* _pt;
    public:
        TIterator_const(T* a = 0)
        {
            _pt = a;
        }

        TIterator_const operator ++ (int)
        {
            TIterator_const a;
            a._pt=_pt;
            _pt++;
            return a;
        }
        TIterator_const operator -- (int)
        {
            TIterator_const a;
            a._pt=_pt;
            _pt--;
            return a;
        }

        TIterator_const& operator ++ ()
        {
            _pt++;
            return *this;
        }
        TIterator_const& operator -- ()
        {
            _pt--;
            return *this;
        }


        bool operator == (const TIterator_const& a) const
        {
            return (_pt==a._pt);
        }
        bool operator != (TIterator_const a) const
        {
            return (_pt!=a._pt);
        }
        void operator += (size_t a)
        {
            _pt=_pt+a;
        }
        void operator -= (size_t a)
        {
            _pt=_pt-a;
        }
        TIterator& operator = (const TIterator &a)
        {
            return (_pt=a._pt);
        }
        bool operator < (TIterator_const a) const
        {
            return (_pt<a._pt);
        }
        bool operator > (TIterator_const a) const
        {
            return (_pt>a._pt);
        }

        T& operator * ()
        {
            return *_pt;
        }
        T& operator [](size_t i)
        {
            return *(_pt+i);
        }
        T& operator->() const
        {
            return &(operator*());
        }
    };

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

    TVector (const T &a, int N=0)//конструктор по умолчанию. размера N с элементами a
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
    size_t size () const
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
        swap(_size, array2._size);
        swap(_capacity,array2._capacity);
        swap(_array,array2._array);
    }
    void resize (int another_size, T a=T())//расширить до Another_size и заполнить a
    {
             if (another_size<_size)
             {
                    if (another_size<(_capacity/2))
                    {
                        T* another_array = new T[another_size*2];
                        for (size_t i=0; i<another_size; ++i)
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
             for (size_t i=0; i<_size; ++i){another_array[i]=_array[i];}
             delete[] _array;
             _array=another_array;
          }
          for (size_t i=_size;i<another_size;++i){_array[i]=a;}
      }
      _size=another_size;
    }



    size_t capacity () const
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
    TIterator begin()
    {
        if(_size==0)
        {
                TIterator iter(NULL);
                return iter;
        }
        TIterator iter(&_array[0]);
        return iter;

    }
    TIterator end()
    {
        if (_size==0)
        {
            TIterator iter(NULL);
            return iter;
        }
        TIterator iter(&_array[0]+_size);
        return iter;

    }
    T& operator[](size_t i)
    {
        if(_size>i)
            return _array[i];
        else return _array[0];
    }
    const T& operator[](size_t i) const
    {
        if(_size>i)
            return _array[i];
        else return _array[0];
    }
    T& back ()
    {
        return ((_size=0)?_array[0]:_array[_size-1]);
    }
    T& front ()
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

    void operator= (TVector<T>& TvArray2)
    {
        _size=TvArray2._size;
        _capacity=TvArray2._capacity;
        _array=TvArray2._array;

    }
};

int main()
{
    TVector<int> array;
    array.push_back(2);		//2 
    array.push_back(4);		//24 
    array.push_back(3);		//243 
    for(TVector<int>::TIterator i=array.begin(); i!=array.end(); ++i) cout<<*i<<" ";
	cout << '\n';
	array.pop_back();	//24 
	for(TVector<int>::TIterator i=array.begin(); i!=array.end(); ++i) cout<<*i<<" ";
	cout << '\n';
	cout << "empty? " << array.empty() <<'\n';
	array.resize(10,0);
	array.resize(7,8);
	array.reserve(20);
	cout << array.size() <<' '<<array.capacity() << '\n';
	array.reserve(4);
	cout << array.size() <<' '<<array.capacity() << '\n';
	for(TVector<int>::TIterator i=array.begin(); i!=array.end(); ++i) cout<<*i<<" ";
	system("PAUSE");
	return 0;
}

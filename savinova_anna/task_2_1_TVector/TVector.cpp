#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class TVector
{
    int* Buf;
	//typedef T* iterator;
	//typedef T* const const_iterator;
public:
	int Size;
	int Capacity;
	void PrintStat()
	{
		cout << "Size: " << Size << " Capacity: " << Capacity << " Is empty: " << empty() << endl;
		cout << "Elements: ";
		for (int i = 0; i < Size; ++i)
			cout << Buf[i] << " ";
		cout << endl;
	}
    TVector()
    {
		Capacity = 16;        
		Size = 0;	
		Buf = new T[Capacity];                
    }	
    ~TVector()
    {
        delete[] Buf;
    }
    void resize()
    {
        Capacity *= 2;
		T* Buf_tmp = new T[Capacity];
        for (int i = 0; i < Size; ++i)
        {
            Buf_tmp[i] = Buf[i];
        }
        delete[] Buf;
        Buf = Buf_tmp;
    }
	void resize(int newCapacity)
	{
		Capacity = newCapacity;
		T* Buf_tmp = new T[Capacity];
        for (int i = 0; i < Size; ++i)
        {
            Buf_tmp[i] = Buf[i];
        }
        delete[] Buf;
        Buf = Buf_tmp;
	}
    bool empty()
    {
		return (Size == 0);
    }
    void clear()
    {
		Size = 0;
    }
    void swap(int a, int b)
    {
		T tmp = Buf[a];
		Buf[a] = Buf[b];
		Buf[b] = tmp;
    }
	/*
    void reserve()
    {
    }
    iterator begin()
    {
    }
    iterator end()
    {
    }
    
    operator [T val]()
    {
    }*/
    //back
    //front
	void push_back(T val)
    {
		if (Size == Capacity)
		{
			resize();
		}
		++Size;
		Buf[Size-1] = val;
    }
    int pop_back()
    {
		--Size;
		return Buf[Size];
    }
	//insert
    //erase
    TVector<T> operator = (TVector<T> oth)
    {
		if (Capacity < oth.Size)
			resize(oth.Capacity);
		Size = oth.Size;
		for (int i = 0; i < Size; ++i)
			Buf[i] = oth.Buf[i];
    }
};

int main()
{
    TVector<int> A;
	A.PrintStat();
	for (int i = 0; i < 35; ++i)
		A.push_back(i);
	A.PrintStat();
	for (int i = 0; i < 5; ++i)
		cout << " Pop: " << A.pop_back();
	cout << endl;
	A.PrintStat();
	A.swap(5,6);
	A.PrintStat();
	TVector<int> B = A;
	B.PrintStat();	
	A.clear();
	A.PrintStat();
    return 0;
}

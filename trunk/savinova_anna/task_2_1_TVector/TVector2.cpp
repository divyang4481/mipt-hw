#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class TVector
{
public:        
        int* Buf;
        int name;
	typedef T* iterator;
	typedef T* const const_iterator;
        int Size;
        int Capacity;
        
        void PrintStat()
        {
                cout << name << " Size: " << Size << " Capacity: " << Capacity << " Is empty: " << empty() << endl;
                cout << "Elements: ";
                for (int i = 0; i < Size; ++i)
                        cout << Buf[i] << " ";
                cout << endl;
        }
        TVector()
        {
                Capacity = 16;        
                Size = 0;
                name = 0;
                begin = Buf;
                end = Buf + 1;
                Buf = new T[Capacity];
                cout << name << " Create" << endl;
        }
        TVector(int val)
        {
                Capacity = 16;        
                Size = 0;
                name = val;
                Buf = new T[Capacity];
                cout << name << " Create" << endl;
        }
        ~TVector()
        {
                cout << name << " Delete" << endl;
                delete[] Buf;
        }
	void resize()
	{
                cout << name << " Resize 2 times" << endl;		
                Capacity *= 2;
		T* Buf_tmp = new T[Capacity];
		for (int i = 0; i < Size; ++i)
			Buf_tmp[i] = Buf[i];
		delete[] Buf;
		Buf = Buf_tmp;
	}
        bool empty()
        {
                return (Size == 0);
        }
        void clear()
        {
                cout << name << " Clear" << endl;
                Size = 0;
        }
        void swap(int a, int b)
        {
                cout << name << " Swap " << a << " " << b << endl;
                T tmp = Buf[a];
                Buf[a] = Buf[b];
                Buf[b] = tmp;
        }
	/*
    void reserve()
    {
    }*/
    /*iterator begin()
    {
    }*/
    /*iterator end()
    {
    }*/
    
        T operator [](int index)
        {
                return Buf[index];      
        }
    //back
    //front
        void push_back(T val)
        {
                cout << name << " Push_back: " << val << endl;
                if (Size == Capacity)
	        	resize();
                
                 Buf[Size] = val;
                 ++Size;
        }
        int pop_back()
        {
                cout << name << " Pop_back: " << Buf[Size-1] << endl;
                --Size;
                return Buf[Size];
        }
	//insert
    //erase
        TVector<T>& operator = (TVector<T>& oth)
        {
                clear();
                for (int i = 0; i < oth.Size; ++i)
                        push_back(oth[i]);
                return *this;
        }
};

int main()
{
        TVector<int> A(1);
        A.PrintStat();
        for (int i = 0; i < 35; ++i)
                A.push_back(i);
        A.PrintStat();        
        TVector<int> B(2);
        B = A;
        B.PrintStat();
        for (int i = 0; i < 5; ++i)
                A.pop_back();
        A.PrintStat();
        B = A;
        B.PrintStat();
        A.swap(5,6);
        A.PrintStat();
        cout << "Test []:" << endl;
        for (int i = 0; i< A.Size; ++i)
                cout << A[i] << " ";
        cout << endl;
	A.clear();
	A.PrintStat();
    return 0;
}

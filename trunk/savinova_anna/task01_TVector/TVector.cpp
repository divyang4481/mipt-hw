#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class TVector
{        
        T* Buf;
        //int name;
        size_t Size;
        size_t Capacity;  
public:        
	typedef T* iterator;
        typedef const T* const_iterator;
        iterator Begin;
        iterator End;
        size_t size() const{
                return Size;
        }
        size_t capacity() const{
                return Capacity;
        }
        iterator begin(){
                return Begin;
        }
        const_iterator cbegin() const{
                return Begin;
        }
        iterator end(){
                return End;
        }
        const_iterator cend() const{
                return End;
        }
        void PrintStat(int name){
                cout << name << " Size: " << Size << " Capacity: " << Capacity << " Is empty: " << empty() << endl;
                cout << "Elements: ";
                for (int i = 0; i < Size; ++i)
                        cout << Buf[i] << " ";
                cout << endl;
        }
        TVector(){
                Capacity = 16;        
                Size = 0;
                Buf = new T[Capacity];
                Begin = Buf;
                End = Begin;
                cout << " Create" << endl;
        }
        /*TVector(int val){
                Capacity = 16;        
                Size = 0;
                name = val;
                Buf = new T[Capacity];
                Begin = Buf;
                End = Begin;
                cout << name << " Create" << endl;
        }*/
        ~TVector(){
                delete[] Buf;
        }
	void resize(){	
                Capacity *= 2;
		T* Buf_tmp = new T[Capacity];
		for (int i = 0; i < Size; ++i)
			Buf_tmp[i] = Buf[i];
		delete[] Buf;
		Buf = Buf_tmp;
                Begin = Buf_tmp;
                End = Buf + Size;
	}
        bool empty() const{
                return (Size == 0);
        }
        void clear(){
                cout << " Clear" << endl;
                Size = 0;
                End = Begin + 1;
        }
        void swap(int a, int b){
                cout << " Swap " << a << " " << b << endl;
                T tmp = Buf[a];
                Buf[a] = Buf[b];
                Buf[b] = tmp;
        }
        void reserve(size_t n){
            while (Capacity < n)
                resize();
        }
        T operator [](int index){
                return Buf[index];
        }
        T& back()
        {
                return Buf[Size-1];
        }
        T& front()
        {
                return Buf[0];
        }
        void push_back(T val){
                if (Size == Capacity)
	                resize();                
                Buf[Size] = val;
                ++Size;
                ++End;
        }
        int pop_back(){
                --Size;
                --End;
                return Buf[Size];
        }
        iterator insert (iterator pos, const T& val){
                if (Size == Capacity)
                        resize();
                for (iterator i = End; i > pos; --i)
                        *i = *(i - 1);
                *(pos + 1) = val;
                ++End;
                ++Size;
                return ++pos;
        }
        void erase(iterator element){
                for (iterator i = element; i != End - 1; ++i)
                        *i = *(i + 1);
                pop_back();        
        }
        TVector<T>& operator = (TVector<T>& oth){
                clear();
                Begin = oth.begin();
                for (int i = 0; i < oth.Size; ++i)
                        push_back(oth[i]);
                return *this;
        }
};

int main()
{
        TVector<int> A;
        A.PrintStat(1);
        for (int i = 0; i < 35; ++i)
                A.push_back(i);
        A.PrintStat(1);        
        TVector<int> B;
        B = A;
        B.PrintStat(2);
        for (int i = 0; i < 5; ++i)
                A.pop_back();
        A.PrintStat(1);
        B = A;
        B.PrintStat(2);
        A.swap(5,6);
        A.PrintStat(1);
        cout << "Test []:" << endl;
        for (int i = 0; i < A.size(); ++i)
                cout << A[i] << " ";
        cout << endl;
        A.clear();
	A.PrintStat(1);
        A = B;
        A.PrintStat(1);
        B.reserve(65);
        B.PrintStat(2);
        TVector<int>::iterator i = A.begin();
        cout << *i << endl;
        for (TVector<int>::const_iterator i = A.cbegin(); i != A.cend(); ++i)
                cout << *i << " ";
        cout << endl;
        A.back() = 5;
        cout << A.back() << endl;
        A.PrintStat(1);
        A.insert(A.begin() + 5, 71);
        A.PrintStat(1);
        A.erase(A.begin() + 7);
        A.PrintStat(1);
        return 0;
}

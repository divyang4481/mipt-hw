#include <vector>
#include <iostream>
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
        size_t size() const{
                return Size;
        }
        size_t capacity() const{
                return Capacity;
        }
        iterator begin(){
                return Buf;
        }
        const_iterator begin() const{
                return Buf;
        }
        iterator end(){
                return (Buf + Size);
        }
        const_iterator end() const{
                return (Buf + Size);
        }
        void PrintStat(char name){
                cout << name << ": Size: " << Size << " Capacity: " << Capacity << " Is empty: " << empty() << endl;
                cout << "Elements: ";
                for (size_t i = 0; i < Size; ++i)
                        cout << Buf[i] << " ";
                cout << endl;
        }
        TVector(){
                Capacity = 16;        
                Size = 0;
                Buf = new T[Capacity];
        }
        TVector(TVector<T> & oth){
                Capacity = oth.Capacity;        
                Size = 0;
                Buf = new T[Capacity];
                for (size_t i = 0; i < oth.Size; ++i)
                        push_back(oth[i]);
        }
        ~TVector(){
                delete[] Buf;
        }
	void resize(size_t n){
		if (n > Size)
                        reserve(n);
                Size = n;
	}
        bool empty() const{
                return (Size == 0);
        }
        void clear(){
                Size = 0;
        }
        void swap(TVector<T>& b){
                std::swap(Size, b.Size);
                std::swap(Capacity, b.Capacity);
                std::swap(Buf, b.Buf);
        }
        void reserve(size_t n){
                while (Capacity < n)
                {           
                        Capacity *= 2;
		        T* Buf_tmp = new T[Capacity];
                        for (size_t i = 0; i < Size; ++i)
			        Buf_tmp[i] = Buf[i];
		        delete[] Buf;
                        Buf = Buf_tmp;
                }
        }
        T& operator [](int index){
                return Buf[index];
        }
        const T& operator [](int index) const{
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
        const T& back() const
        {
                return Buf[Size-1];
        }
        const T& front() const
        {
                return Buf[0];
        }
        void push_back(T val){
                if (Size == Capacity)
	                reserve(Size + 1);
                Buf[Size] = val;
                ++Size;
        }
        int pop_back(){
                --Size;
                return Buf[Size];
        }
        iterator insert (iterator pos, const T& val){
                if (Size == Capacity)
                        reserve(Size + 1);
                for (iterator i = end(); i > pos; --i)
                        *i = *(i - 1);
                *(pos + 1) = val;
                ++Size;
                return ++pos;
        }
        void erase(iterator element){
                for (iterator i = element; i != end() - 1; ++i)
                        *i = *(i + 1);
                pop_back();        
        }
        TVector<T>& operator = (TVector<T>& oth){
                clear();
                for (size_t i = 0; i < oth.Size; ++i)
                        push_back(oth[i]);
                return *this;
        }
};

struct S
{
        int val;
        static size_t Created;
        static size_t Deleted;
        S()
        {
                val = 0;
                ++Created;
        }
        S(S& oth)
        {
                val = oth.val;
                ++Created;
        }
        ~S()
        {
                ++Deleted;
        }
};

size_t S::Created = 0;
size_t S::Deleted = 0;

int main()
{
        cout << "Create A" << endl;
        TVector<int> A;
        A.PrintStat('A');
        cout << "Filling A" << endl;
        for (size_t i = 0; i < 35; ++i)
                A.push_back(i);
        A.PrintStat('A');
        cout << "Create B = A" << endl;
        TVector<int> B = A;
        B.PrintStat('B');
        for (int i = 0; i < 5; ++i)
        {
                int tmp = A.pop_back();
                cout << "Pop_back: " << tmp << endl;
        }
        A.PrintStat('A');
        cout << "Swap A, B" << endl;
        A.swap(B);
        A.PrintStat('A');
        B.PrintStat('B');
        cout << "Test [] A[6] = 1003" << endl;
        A[6] = 1003;
        A.PrintStat('A');
        cout << "Clear A" << endl;
        A.clear();
	A.PrintStat('A');
        cout << "A = B" << endl;
        A = B;
        A.PrintStat('A');
        cout << "Reserve 65" << endl;
        B.reserve(65);
        B.PrintStat('B');
        cout << "Test iterator" << endl;
        TVector<int>::iterator i = A.begin();
        cout << *i << endl;
        for (TVector<int>::const_iterator i = A.begin(); i != A.end(); ++i)
                cout << *i << " ";
        cout << endl;
        cout << "Test back() = 5" << endl;
        A.back() = 5;
        cout << "A.back() = " << A.back() << endl;
        A.PrintStat('A');
        cout << "Test insert insert(A.begin() + 5, 71)" << endl;
        A.insert(A.begin() + 5, 71);
        A.PrintStat('A');
        cout << "Test erase(A.begin() + 7)" << endl;
        A.erase(A.begin() + 7);
        A.PrintStat('A');
        cout << "Memory test" << endl;
        {
                TVector<S> C;
        };
        cout << "Created: "<< S::Created << " Deleted: "<< S::Deleted << endl;        
        return 0;
}

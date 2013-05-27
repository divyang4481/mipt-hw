#include <iostream>
#include <vector>

using namespace std;

template <typename T>

class TVector {
public:
    int size;
    int capacity;
    T *buf;
    
    typedef T* iterator;
    typedef const T* const_iterator;
        
        TVector() {
                size = 0;
                capacity = 1;
                buf = new T[capacity];
        }
		TVector(TVector<T> & oth){
                Capacity = oth.Capacity;        
                Size = 0;
                Buf = new T[Capacity];
                for (size_t i = 0; i < oth.Size; ++i)
                push_back(oth[i]);
        }
        ~TVector() {
                size = 0;
                capacity = 0;
                delete[] buf;
        }

        int Size() const {
                return size;
        }

        bool Empty() const {
        return(size == 0);
    }

        void Clear() {
                size = 0;
        }

        void Swap(TVector &other) { //!!
                swap(*this.buf, other.buf);
                swap(*this.size, other.size);
                swap(*this.buf, other.buf);
        }

        void Resize() {
				while (capacity < n) 
                        Reserve(n);    

        }

        void Reserve(int n) { 
			capacity *= 2;
                T* buf_new = new T[capacity];
                for (int i = 0; i < size - 1; ++i) {
                        buf_new[i] = buf[i];
                }
                delete buf;
                buf = buf_new;    
        }
        
        int Capacity() const {
                return(capacity);
        }

        iterator Begin() {
                return(buf);
        }
        const_iterator begin() const{
                return Buf;
		}
        iterator End() {
                return(buf + size);
        }
        const_iterator end() const{
                return (Buf + Size);
		}
        T& operator[](int n) {
                if (n <= size && n >= 0 )
                        return(buf[n]);
                else
                        cout << "wrong index" << endl;
        }
        
        T& Front() const {
                return(buf[0]);
        }

        T& Back() const {
                return(buf[size - 1]);
        }

        void Push_back(T n) {
                size++;
                Reserve(size);
                buf[size - 1] = n;
        }

        void Pop_back() {
                size--;
        }

        void Insert (iterator ind, const T& n) {
                size++;
                Reserve(size);
                for(iterator i = End(); i != ind; --i) {
                        *i = *(i - 1);
                }
                *ind = n;
        }

        void Erase(iterator ind) {
                for (iterator i = ind; i != End(); ++i)
                        *i = *(i + 1);
                size--;
        } 
        TVector& operator= (TVector& other) /*const?*/ {
                delete[] buf;
                size = other.Size();
                capacity = other.Capacity();
                buf = new T[size];
                for (int i = 0; i < other.Size(); ++i)
                        Push_back(other[i]);
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

int main() {
        

	//freopen("output.txt", "w", stdout);

        TVector<int> V1;

        cout << "Empty? " << V1.Empty() << " Size: " << V1.Size() << " Capacity: " << V1.Capacity() << endl;
        cout << "V1: " << endl;
        for (int i = 0; i < 10; ++i) {
                V1.Push_back(i);
            cout << V1[i] << endl;
        }
        cout << "Empty? " << V1.Empty() << " Size: " << V1.Size() << " Capacity: " << V1.Capacity() << endl;
        cout << "First element: " << V1.Front() << " Last element: " << V1.Back() << endl;

        ////for swap
        //TVector<int> V2;
        //for (int i = 9; i >= 0; --i) {
        //      V2.Push_back(i);
        //}     
        //cout << "V2: " << endl;
        //for (int i = 0; i < 10; ++i) {
        //    cout << V2[i] << endl;
        //}

//      V1.Pop_back();
//      for (int i = 0; i < V1.Size(); ++i) {
//          cout << V1[i] << endl;
//      }

        V1.Insert(V1.Begin(), 11);
        cout << "V1: " << endl; 
        for (int i = 0; i < V1.Size(); ++i) {
            cout << V1[i] << endl;
        }

        V1.Erase(V1.Begin());
        cout << "V1: " << endl; 
        for (int i = 0; i < V1.Size(); ++i) {
            cout << V1[i] << endl;
        }
        
		{TVector <S> kekeke;}
		cout << S::Created << " " << S::Deleted; 

        return 0;
}
#include <iostream>
#include <vector>

using namespace std;

template <typename T>

class TVector {
    int size;
    int capacity;
    T *buf;
public:    
    typedef T* iterator;
    typedef const T* const_iterator;
        
        TVector() {
                size = 0;
                capacity = 8;
                buf = new T[capacity];
        }

		void Push_back(T val) {
                if (size == capacity)
                        Reserve(size + 1);
                buf[size] = val;
                ++size;
        }

		TVector(TVector<T> & oth) {
                capacity = oth.capacity;        
                size = 0;
                buf = new T[capacity];
                for (int i = 0; i < oth.Size(); ++i)
					Push_back(oth[i]);
        }
        ~TVector() {
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

        void Resize(int n) {
                if (size < n) 
                     Reserve(n);    
				size = n;
        }

        void Reserve(int n) { 
                while (capacity < n)
                {           
                        capacity *= 2;
                        T* buf_tmp = new T[capacity];
                        for (int i = 0; i < size; ++i)
                                buf_tmp[i] = buf[i];

						delete[] buf;
                        buf = buf_tmp;
                }
        }
        
        int Capacity() const {
                return(capacity);
        }

        iterator Begin() {
                return(buf);
        }
        const_iterator begin() const{
                return buf;
                }
        iterator End() {
                return(buf + size);
        }
        const_iterator end() const{
                return (buf + size);
        }
        T& operator [](int index){ 
				return buf[index];
        }
        const T& operator [](int index) const{   
				return buf[index];
        }
        
        T& Front() const {
                return(buf[0]);
        }

        T& Back() const {
                return(buf[size - 1]);
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
        static int Created;
        static int Deleted;
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

int S::Created = 0;
int S::Deleted = 0;

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
        
        {TVector <S> memtest;}
        cout << S::Created << " " << S::Deleted << "\n"; 
		if (S::Created == S::Deleted)
			cout << "NO memory leaks" << "\n";
		else
			cout << "ERROR! Have memory leaks" << "\n";

        {TVector <S> memtest1;
		 TVector <S> memtest2(memtest1);
     	}
        cout << S::Created << " " << S::Deleted << "\n"; 
		if (S::Created == S::Deleted)
			cout << "NO memory leaks" << "\n";
		else
			cout << "ERROR! Have memory leaks" << "\n";
			


		return 0;
}

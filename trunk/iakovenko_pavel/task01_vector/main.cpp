#include <iostream>
using namespace std;


template <typename T>
class TVector{
public:
	class iterator{
		friend class TVector;
	public:
		iterator(T* t):el(t){}
		iterator():el(0){
		};
		iterator (iterator& another){
			el = another.el;
		}
		iterator& operator= (iterator& another){
			el = another.el;
			return *this;
		}
		void operator++(){
			el++;
		};

		void operator --(){
			el--;
		}

		T& operator *(){
			return *el;
		}

		bool operator== (iterator& i){
			return (el == i.el ? true:false);
		}

		bool operator!= (iterator& i){
			return !(*this == i);
		}

		T* get(){
			return el;
		}

		int operator-(iterator tp){
			T* t=el;
			int i=0;
			for(; t!=tp.get(); t++, i++);
			return i;
		}

		iterator operator+(int n){
			for (int i=0; i<n; ++i)
				++*this;
			return *this;
		}

	private:
		T* el;
	};
	class const_iterator{
		friend class TVector;
	public:
		const_iterator(T *t):el(t){}
		const_iterator():el(0){
		};

		void operator++(){
			el++;
		};

		void operator --(){
			el--;
		}

		const T& operator *()const {
			return *el;
		}
		const_iterator (const_iterator& another){
			el = another.el;
		}
		const_iterator& operator= (const_iterator& another){
			el = another.el;
			return *this;
		}

		bool operator == (const_iterator& i){
			return (el == i.el ? true:false);
		}

		bool operator != (const_iterator& i){
			return !(*this == i);
		}

		T* get(){
			return el;
		}

		int operator-(const_iterator tp){
			T* t=el;
			int i=0;
			for(; t!=tp.get(); t++, i++);
			return i;
		}

		const_iterator operator+(int n){
			for (int i=0; i<n; ++i)
				++*this;
			return *this;
		}

	private:
		T* el;
	};
private:
	int position(iterator pos){
		T* tp=arr;
		unsigned int i;
		for(i=0; tp!=pos.get(); ++tp, ++i);
		return i;
	}
public:


	TVector(){
		tsize=0;
		tcapacity=10;
		arr=new T [tcapacity];
	};


	TVector(unsigned int f_cap){
		tsize=0;
		tcapacity=f_cap;
		arr=new T [tcapacity];
	};

	TVector(int n, T value){
		tsize=n;
		tcapacity=n;
		arr=new T [tcapacity];
		for (int i = 0;  i < n; ++i)
			arr[i] = value;
	}

	TVector ( iterator  beg, iterator  end){
		tsize = 0;
		tcapacity = 10;
		arr = new T[tcapacity];
		for (;beg!= end; ++beg)
			push_back(*beg);
	}

	~TVector(){
		delete[] arr;
	};

	void push_back(T n){
		if (tsize==tcapacity){
			T* tptr=new T[tcapacity*=2];
			for(unsigned int i=0; i<tsize; i++)
				tptr[i]=arr[i];
			delete [] arr;
			arr=tptr;
		}
		arr[tsize]=n;
		tsize++;
	};

	iterator begin(){
		iterator pos (arr);
		return pos;
	}

	iterator end(){
		iterator pos (arr + tsize);
		return pos;
	}

	const_iterator cbegin(){
		const_iterator pos (arr);
		return pos;
	}

	const_iterator cend(){
		const_iterator pos (arr +  tsize);
		return pos;
	}

	T pop_back(){
		return arr[--tsize];
	};

	void clear(){
		tsize=0;
		return;
	};

	void swap(TVector& temp){
		std::swap(arr, temp.arr);
		std::swap(tcapacity, temp.tcapacity);
		std::swap(tsize, temp.tsize);
		return;
	}

	void reserve (unsigned int ncap){
		if (ncap<=tsize)
			return; 
		T* tp=new T [ncap];
		for(unsigned int i=0; i<tsize; i++)
			tp[i]=arr[i];
		delete[] arr;
		arr=tp;
		tcapacity=ncap;
		return;
	}

	T& operator[](unsigned int n){ //как сделать так, чтобы записывать?
		return arr[n];
	};

	TVector& operator=(const TVector& temp){
		if(temp.size()> tcapacity){
			while(temp.size()> tcapacity)
				tcapacity*=2;
			delete [] arr;
			arr=new T [tcapacity];
		}
		for (unsigned int i=0; i<temp.size(); i++)
			arr[i]=temp[i];
		tsize=temp.size();
		return *this;
	};

	unsigned int size(){
		return tsize;
	};

	unsigned int capacity(){
		return tcapacity;
	};

	bool empty (){
		if (tsize==0)
			return true;
		return false;
	};

	T& back(){
		return arr[tsize-1];
	};

	T& front(){
		return arr[0];
	};

	void resize(unsigned int n){
		if(n==tsize)
			return;
		else if (n<tsize){
			unsigned int i=tsize;
			for (;i>n; i--){
				tsize--;	
			}
		}
		else if (n>tsize)
			if(n>tcapacity){
				while (n>tcapacity){
					tcapacity*=2;
				}
				T* tptr=new T[tcapacity];
				for(unsigned int i=0; i<tsize; i++)
					tptr[i]=arr[i];
				for (unsigned int i=tsize; i<n; i++)
					tptr[i]=0;
				delete[] arr;
				arr=tptr;
			}
			else
				for (unsigned int i=tsize; i<n; i++)
					arr[i]=0;
		tsize=n;
		return;
	};

	iterator erase(iterator pos){ //Как это сделать красивее? Вычитать!
		T* tp=arr;
		unsigned int i;
		for(i=0; tp!=pos.get(); ++tp, ++i);
		tsize-=1;
		++pos;
		for(unsigned int k=i;k<tsize; k++){
			arr[k]=arr[k+1];
		}
		return pos;
	}

	iterator erase(iterator beg, iterator end){ 
		T* tp=arr;
		int i;
		for(i=0; tp!=beg.get(); ++tp, ++i);
		int k;
		for(k=0; tp!=end.get(); ++tp, ++k);
		unsigned int p = 0;
		for(unsigned int j=i; (k+p-1)<tsize; j++){
			arr[j]=arr[k+p-1];
			++p;
		}
		tsize=tsize-k+i+1;
		++end;
		return end;
	}

	iterator insert(iterator it, int n, T val){
		insert(position(it), n, val);
		for (int i=0; i<n; ++i)
			--it;
		return it;
	}

	void insert(int p, int n, T val){
		if((tsize+n)>=tcapacity)
			reserve(tsize+n);
		tsize+=n;
		for(int i=tsize-1; i>=(p+n); i--)
			arr[i]=arr[i-n];
		for(int i=p; i<p+n; ++i)
			arr[i]=val;
		return;
	}

	iterator insert(iterator pos, iterator beg, iterator end){ 
		int p=position(pos);
		--end;
		for (; beg!=end; --end,--pos)
			insert(p, 1, *end);
		insert(p,1,*beg);
		return --pos;
	}

	iterator insert(iterator pos, T* beg, T* end){
		int p=position(pos);
		--end;
		for (; beg!=end; --end, --pos)
			insert(p, 1, *end);
		insert(p,1,*beg);
		return --pos;
	}

private:
	unsigned int tsize;
	unsigned int tcapacity;
	T* arr;
	friend void show();
};


template <typename T>
void show(TVector<T>& a){
		TVector <T> :: const_iterator pos = a.cbegin();
		for (int i=0; pos!=a.cend(); ++pos, ++i)
			cout<< "a["<<i<<"]="<<*pos<<endl;
		cout<<"-----------------------------------------"<< endl;
}


int main(){
	TVector<int>a,b;
	for (int i=0; i<10; i++)
		a.push_back(i);
	for (int i=9; i>=0; i--)
		b.push_back(i);
	TVector<int>::iterator pos;
	int ab;
	for(int i=9; i>=6; i--)
		ab=a.pop_back();
	cout << a.size()<<endl;
	a.clear();
	cout<< a.empty()<< endl;
	show(a);
	a.swap(b);
	show(a);
	show(b);
	a.resize(8);
	show(a);
	a.reserve(5);
	show(a);
	a.reserve(25);
	show(a);
	TVector<int>::iterator end=a.end();
	for (pos=a.begin(); pos!=end; ++pos)
		*pos=5;
	show(a);
	cout << a.front()-a.back()<<endl;
	a.insert(a.begin()+7, 5, 100);
	show(a);
	a.erase(a.begin(), a.begin()+3);
	show(a);
	return 0;

}
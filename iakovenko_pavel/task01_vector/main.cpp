#include <iostream>
using namespace std;


template <typename T>
class TVector{
public:
	class iterator{
		friend class TVector;
		iterator(T *t):el(t){}
	public:
		iterator():el(0){
		};

		void operator++(){
			el++;
		};

		void operator --(){
			el--;
		}

		T& operator *(){
			return *el;
		}

		bool operator == (iterator& i){
			return (el == i.el ? true:false);
		}

		bool operator != (iterator& i){
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
public:
	static int Created;
	static int Deleted;
	TVector(){
		tsize=0;
		tcapacity=10;
		arr=new T [tcapacity];
		rehersal();
		++Created;
	};

	void rehersal (){
		beg=arr;
		ed=arr+tcapacity;
		Begin=iterator(beg);
		End=iterator(ed);
	}

	TVector(unsigned int f_cap){
		tsize=0;
		tcapacity=f_cap;
		arr=new T [tcapacity];
		beg=arr;
		ed=arr+tcapacity;
		Begin=iterator(beg);
		End=iterator(ed);
		++Created;
	};

	~TVector(){
		delete[] arr;
		++Deleted;
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
		return Begin;
	}

	iterator end(){
		return End;
	}

	T pop_back(){
		return arr[--tsize];
	};

	void clear(){
		tsize=0;
		return;
	};

	void swap(TVector& temp){
		TVector tp;
		tp=*this;
		*this=temp;
		temp=tp;
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
		rehersal();
		return;
	}

	T& operator[](unsigned int n){ //как сделать так, чтобы записывать?
		if (n>=tsize)
			cout << "error!\n";   //как вывести здесь ошибку? как это сделать красиво?
		return arr[n];
	};

	TVector& operator=(TVector& temp){
		if(temp.size()> tcapacity){
			while(temp.size()> tcapacity)
				tcapacity*=2;
			delete [] arr;
			arr=new T [tcapacity];
		}
		for (unsigned int i=0; i<temp.size(); i++)
			arr[i]=temp[i];
		tsize=temp.size();
		rehersal();
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
		if (tsize==0)
			cout << "error!"<< endl;
		return arr[tsize-1];
	};

	T& front(){
		if (tsize==0)
			cout << "error!"<< endl;
		return arr[0];
	};

	int position(iterator pos){
		T* tp=arr;
		unsigned int i;
		for(i=0; tp!=pos.get(); ++tp, ++i);
		return i;
	}

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
		rehersal();
		return;
	};
	
	void erase(iterator pos){ //Как это сделать красивее? Вычитать!
		T* tp=arr;
		unsigned int i;
		for(i=0; tp!=pos.get(); ++tp, ++i);
		tsize-=1;
		for(unsigned int k=i;k<tsize; k++){
			arr[k]=arr[k+1];
		}
	}

	void erase(iterator beg, iterator end){ 
		T* tp=arr;
		int i;
		for(i=0; tp!=beg.get(); ++tp, ++i);
		int k;
		for(k=0; tp!=end.get(); ++tp, ++k);
		unsigned int p=0;
		for(unsigned int j=i, p=0; (k+p-1)<tsize; j++, p++)
			arr[j]=arr[k+p-1];
		tsize=tsize-k+i+1;
	}

	void insert(iterator it, int n, T val){
		insert(position(it), n, val);
		return;
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

	void insert(iterator pos, iterator beg, iterator end){ //что происходит с другим вектором? 
		int p=position(pos);
		--end;
		for (; beg!=end; --end)
			insert(p, 1, *end);
		insert(p,1,*beg);
		return;
	}

	void insert(iterator pos, T* beg, T* end){
		int p=position(pos);
		--end;
		for (; beg!=end; --end)
			insert(p, 1, *end);
		insert(p,1,*beg);
		return;
	}

	void show(){
		for (unsigned int i=0; i<tsize; i++)
			cout<< "a["<<i<<"]="<<arr[i]<<endl;
		cout<<"-----------------------------------------"<< endl;
		return;
	}

private:
	T *beg;
	T *ed;
	unsigned int tsize;
	unsigned int tcapacity;
	T* arr;
	iterator Begin;
	iterator End;
};

int TVector<int>:: Created=0;
int TVector<int>:: Deleted=0;

int main(){
	{TVector<int>a,b;
	for (int i=0; i<10; i++)
		a.push_back(i);
	for (int i=9; i>=0; i--)
		b.push_back(i);
	TVector<int>::iterator pos;
	int ab;
	for(int i=9; i>=6; i--)
		ab=a.pop_back();
	a.show();
	cout << a.size()<<endl;
	a.clear();
	cout<< a.empty()<< endl;
	a.show();
	a.swap(b);
	a.show();
	b.show();
	a.resize(8);
	a.show();
	a.reserve(5);
	a.show();
	a.reserve(25);
	a.show();
	for (pos=a.begin(); pos!=a.end(); ++pos)
		*pos=5.0;
	a.show();
	cout << a.front()-a.back()<<endl;
	a.insert(a.begin()+7, 5, 100);
	a.show();
	a.erase(a.begin(), a.begin()+3);
	a.show();
	}
	cout << TVector<int>::Created<<endl<<TVector<int>::Deleted<<endl;
	system("pause");
	return 0;
}
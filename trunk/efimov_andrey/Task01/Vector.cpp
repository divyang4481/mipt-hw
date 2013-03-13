#include <iostream>

using namespace std;

const int DefaultCap=10;
const int Multiplier=2;

void SizeErrorWarn(int f){
	switch (f){
	case 1:
		cout << "Swap ";
		break;
	case 2:
		cout << "Back ";
		break;
	case 3:
		cout << "Front ";
		break;
	case 4: 
		cout << "Operator [] ";
		break;
	default:
		cout << "Something ";
	}
	cout << "not completed: chosen number is out of size range" << endl;
}

template <typename T>
class TVector{
public:
	class iter{
		friend class vector;
		iter(T *t):target(t){}
	private:
		T* target;
	public:
		iter():target(0){
		};
		void operator++(){
			target++;
		}
		void operator--(){
			target--;
		}
		T& operator *(){
			return *target;
		}
		bool operator == (iter& i){
			return (target=i.target?true:false);
		}
		bool operator != (iter& i){
			return !(*this=i);
		}
		T* content(){
			return target;
		}
		int operator-(iter other){
			T* c=target;
			int i=0;
			for (; t!=target.get(); t++, i++);
			return i;
		}
	};
	TVector(int custom_cap){
		vsize=0;
		vcapacity=custom_cap;
		cont=new T[vcapacity];
		setup;
	}
	TVector(){
		TVector(DefaultCap);
	}
	TVector(T* a, int original_size){
		TVector(original_size);
		vsize=original_size;
		for (int i=0; i<original_size; ++i){
			cont[i]=a[i];
		}
	}
	~TVector(){
		delete[] cont;
	}
	unsigned int size(){
		return vsize;
	}
	unsigned int capacity(){
		return vcapacity;
	}
	bool empty(){
		return tsize==0;
	}
	iter begin(){
		return begI;
	}
	iter end(){
		return endI;
	}
	void reserve(unsigned int ncapacity){
		if (ncapacity<vcapacity) return;
		T* newcont = new T[ncapacity];
		for (unsigned int i=0; i<vsize; ++i){
			newcont[i]=cont[i];
		}
		delete[] cont;
		cont=newcont;
		setup();
	}
	int findnum(iter pos){
		T* tp=cont;
		unsigned int i=0;
		for (; tp!=pos.content(); ++i, ++tp);
		return i;
	}
	T& back(){
		if (vsize!=0)
			return cont[vsize-1];
		else ErrorWarn(2);
	}
	T& front(){
		if (vsize!=0)
			return cont[0];
		else ErrorWarn(3);
	}
	void swap(unsigned int n1, unsigned int n2){
		if (max(n1, n2)<vsize){
			T whoop=cont[n1];
			cont[n1]=cont[n2];
			cont[n2]=whoop;
		}
		else ErrorWarn(1);
	}
	void clear(){
		vsize=0;
		vcapacity=DefaultCap;
		delete[] cont;
		T* cont = new T[vcapacity];
		return;
	}
	void insert(iter it, int n, T val){
		insert(findnum(it), n, val);
	}
	void insert(int pos, int n, T val){
		reserve(vsize+n);
		vsize+=n;
		for(int i=vsize-1; i>=(pos+n); i--)
			cont[i]=cont[i-n];
		for(int i=pos; i<pos+n; ++i)
			cont[i]=val;
		return;
	}
	void insert(iter it, iter Sbeg, iter Send){
		iter pos=findnum(it);
		iter cur=--Send;
		for (;cur!=Sbeg; cur--)
			insert(pos, 1, *cur);
		insert(pos, 1, *Sbeg);
		return;
	}
	void push_back(T source){
		made_bigger();
		cont[vsize]=source;
		++vsize;
	}
	T pop_back(){
		T temp=cont[--vsize];
		made_smaller();
		return temp;
	}
	void resize(unsigned int n){
		if (n==vsize) return;
		bool f = (vsize<n);
		vsize=n;
		if (f) made_bigger();
		if (!f) made_smaller();
	}
	void erase(iter pos){
		T* temp=cont;
		unsigned int start;
		unsigned int cur;
		start=findnum(pos);
		vsize--;
		for(cur=i; cur<vsize; cur++)
			cont[cur]=cont[cur+1];
		made_smaller();
	}
	void erase(iter Pbeg, iter Pend){
		T* temp=cont;
		int start=findnum(Pbeg);
		int finish=findnum(Pend);
		unsigned int i=start;
		int length=finish-start+1;
		for (;i<vsize-length; ++i){
			cont[i]=cont[i+length];
		}
		vsize-=length;
		made_smaller();
	}
	bool operator = (TVector other){
		resize(other.vsize)
		for (unsigned int i=0; i<vsize; ++i)
			cont[i]=other.cont[i];
		return true;
	}
	T operator [] (unsigned int n){
		if (n<size) return cont[n];
		SizeErrorWarn(4);
		return cont[size];
	}
private:
	T* begT;
	T* endT;
	unsigned int vsize;
	unsigned int vcapacity;
	T* cont;
	iterator begI;
	iterator endI;
	void made_bigger(){
		while (vsize>=vcapacity){
			T* newcont = new T[vcapacity*=Multiplier];
			for (unsigned int i=0; i<vsize; ++i){
				newcont[i]=cont[i];
			}
			delete[] cont;
			cont=newcont;
			setup();
		}
	}
	void made_smaller(){
		while (vsize<vcapacity/(Multiplier*Multiplier)){
			T* newcont = new T[vcapacity/=Multiplier];
			for (unsigned int i=0; i<vsize; ++i){
				newcont[i]=cont[i];
			}
			delete[] cont;
			cont=newcont;
			setup();
		}
	}
	void setup(){
		begT=cont;
		endT=cont+capacity;
		begI=iterator(begT);
		endI=iterator(endT);
	}
};

int main(){


}
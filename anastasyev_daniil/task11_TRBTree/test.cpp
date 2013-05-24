#include <vector>
#include <string>
#include <iostream>
#include "rbt.h"
#include <stdlib.h>
using namespace std;

template <typename T>
struct TFoo
{
    T Value;
    TFoo() : Value(T(0)) { ++Created; }
	TFoo(T v): Value(v) { ++Created; }
    TFoo(const TFoo &other) : Value(other.Value) { ++Created; }
    ~TFoo() { ++Deleted; }
    bool operator< (const TFoo& other) const
    {
        return Value < other.Value;
    }
    TFoo& operator= (const TFoo& other)
    {
        Value = other.Value;
		return *this;
    }
    TFoo& operator= (T r)
    {
        Value = r;
		return *this;
    }
	void operator += (const TFoo &other)
	{
		Value += other.Value;
	}
	void operator -= (const TFoo &other)
	{
		Value -= other.Value;
	}
	void operator *= (const TFoo &other)
	{
		Value *= other.Value;
	}
	TFoo operator+ (const TFoo &other) const
	{
		TFoo temp(*this);
		temp+=other;
		return temp;
	}
	TFoo operator- (const TFoo &other) const
	{
		TFoo temp(*this);
		temp-=other;
		return temp;
	}
	TFoo operator*(const TFoo &other) const
	{
		TFoo temp(*this);
		temp *= other;
		return temp;
	}
	TFoo operator* (T v) const
	{
		TFoo temp(*this);
		temp.Value*=v;
		return temp;
	}
	bool operator== (const TFoo &a) const
	{
		return (Value == a.Value);
	}
	static int Created;
    static int Deleted;
    static void PrintStats()
	{
        cout << "TFoo::Created = " << Created << endl << "TFoo::Deleted = " << Deleted << endl;
    }
};
template<> int TFoo<int>::Created = 0;
template<> int TFoo<int>::Deleted = 0;

template <typename T>
ostream& operator<< (ostream &out, const TFoo<T> &t)
{
	out << t.Value;
    return out;
};


int main()
{
	{
		TRBTree<TFoo<int> > set1;
		cout<<"set1 inserting: ";
		for (int i=0; i<10; ++i)
		{
			int k = rand()%100;
			set1.insert(k);
			cout <<k << " ";
		}
		cout << endl<< "set1: ";
		TRBTree<TFoo<int> >::iterator it = set1.begin(), end = set1.end();
		for (; it!= end; ++it)
			cout << *it << " ";
		pair<TRBTree<TFoo<int> >::iterator, bool> res = set1.insert(24);
		cout<<endl<<"set1.insert(24) ";
		if (res.second) cout<<"Already here"<<endl;
		else cout << "New element "<<endl;
		set1.erase(set1.begin());
		cout<<"set1.erase(res.first)"<<endl;
		it = set1.begin(), end = set1.end();
		for (; it!= end; ++it)
			cout << *it << " ";
		cout<<endl;
		it = set1.find(69);
		if (it != end)
			cout << "Find 69 in set1"<<endl;
		else
			cout << "Cant find 69 in set1"<<endl;
		TRBTree<TFoo<int> > set2;
		cout<<"set2 inserting: ";
		for (int i=0; i<10; ++i)
		{
			int k = rand()%100;
			set2.insert(k);
			cout <<k << " ";
		}
		cout << endl<< "set2: ";
		it = set2.begin(); end = set2.end();
		for (; it!= end; ++it)
			cout << *it << " ";
		set1.swap(set2);
		cout << endl << "swap(set1, set2)"<<endl;
		cout << endl<< "set1: ";
		it = set1.begin(); end = set1.end();
		for (; it!= end; ++it)
			cout << *it << " ";
		cout << endl<< "set2: ";
		it = set2.begin(); end = set2.end();
		for (; it!= end; ++it)
			cout << *it << " ";
		cout<<endl;
	}
	TFoo<int>::PrintStats();
	return 0;
}


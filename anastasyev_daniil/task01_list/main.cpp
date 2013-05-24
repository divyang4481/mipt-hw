#include <iostream>
#include <list>
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
        cout << "TFoo::Created = " << Created << endl
            << "TFoo::Deleted = " << Deleted << endl;
    }
};


template<> int TFoo<int>::Created = 0;
template<> int TFoo<int>::Deleted = 0;


template <typename T>
class TList
{

	struct TNode
	{
	friend class TList;
		T val;
		TNode *prev, *next;
		TNode()
		{
			val = 0;
			prev = 0;
			next = 0;
		}
		TNode(T v)
		{
			val = v;
			prev = 0;
			next = 0;
		}
		TNode(TNode &t)
		{
			val = t.val;
			prev = t.prev;
			next = t.next;
		}
		TNode(T v, TNode *p, TNode *n)
		{
			val = v;
			prev = p;
			next = n;
		}
		~TNode()
		{}
	};

public:
	class iterator
	{
		TNode  *node;
	public:
		friend class TList;
		iterator(): node(T(0)){}
		iterator(TNode *t): node(t){}
		T& operator *()
		{
			return node->val;
		}
		iterator& operator ++()
		{
			node = node->next;
			return *this;
		}
		iterator& operator --()
		{
			node = node->prev;
			return *this;
		}
		iterator operator ++(int)
		{
			iterator it(*this);
			++(*this);
			return it;
		}
		iterator operator --(int)
		{
			iterator it(*this);
			--(*this);
			return it;
		}
		bool operator ==(const iterator& other)
		{   
			return (node==other.node);
		}
		bool operator !=(const iterator& other)
		{   
			return (!(*this==other));
		}
		T* operator ->() const
		{
			return (&(node->val));
		}
		TNode* nd()
		{
			return node;
		}
	};

	class const_iterator
	{
		TNode  *node;
		TNode* nd()
		{
			return node;
		}
	public:
		friend class TList;
		const_iterator(): node(T(0)){}
		const_iterator(TNode *t): node(t){}
		const T& operator *()
		{
			return node->val;
		}
		const_iterator& operator ++()
		{
			node = node->next;
			return *this;
		}
		const_iterator& operator --()
		{
			node = node->prev;
			return *this;
		}
		const_iterator operator ++(int)
		{
			iterator it(*this);
			++(*this);
			return it;
		}
		const_iterator operator --(int)
		{
			iterator it(*this);
			--(*this);
			return it;
		}
		bool operator ==(const const_iterator& other)
		{   
			return (node==other.node);
		}
		bool operator !=(const const_iterator& other)
		{   
			return (!(*this==other));
		}
		const T* operator ->() const
		{
			return (&(node->val));
		}

	};
private:
    TNode *first, *last;
    void Insert(TNode* where, T val)
    {
        TNode *p = new TNode(val);
        Insert(where, p);
    }
	void Insert(TNode* where, TNode* p)
	{
		if (where==first)
		{
			Push_front(p->val);
			delete p;
		}
		else 
		{
			p->prev = where->prev;
			p->next = where;
			where->prev->next = p;
			where->prev = p;
		}	
	}
	void Extract(TNode* p)
	{
		if (p == first && p == last->prev)
		{
			first=0;
			delete p;
			last->prev = 0;
			last->next = 0;
			return;
		}
		if (p==first)
			first = p->next;
		else
			p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;	
	}
public:
    TList()
    {
        first = 0;
        last = new TNode;
		last->next = 0;
		last->prev = 0;
    }
    TList(TList &lst)
    {
        if (lst.first==0) 
        {
            TList();
            return;
        }
		*this = lst;
    }
    ~TList()
    {
		Clear();
		delete last;
    }
	bool Empty() const
	{
		return (first == 0);
	}
	iterator Begin()
	{
		return iterator(first);
	}
	iterator End()
	{
		return iterator(last);
	}
	const_iterator Begin() const 
	{
		return iterator(first);
	}
	const_iterator End() const 
	{
		return iterator(last);
	}
	void Clear()
	{
        while (first != last && first != 0)
        {
            TNode *p=first -> next;
            delete first;            
            first = p;
        }
		first = 0;
	}
	void Swap(TList& other)
	{
		swap(first, other.first);
		swap(last, other.last);
	}
	void Push_back(T val)
    {
        TNode *node = new TNode(val);
		node->next = last;
        if (first == 0)
		{
			first = node;
		}
        else 
		{
			node->prev = last->prev;
			last->prev->next = node;
		}
        last->prev = node;
    }
    void Push_front(T val)
    {
        TNode *node = new TNode(val);
		node->next = first;
        if (first != 0)
            first->prev = node;
        else 
		{	
			last->prev = node;
			node->next = last;
		}
        first = node;
    }

	void Insert(iterator pos, T val)
	{
		Insert(pos.nd(), val);
	}
	void Insert(iterator pos, iterator first, iterator last)
	{
		--last;
		for (; first!=last; --last, --pos)
			Insert(pos.nd(), *last);
		Insert(pos.nd(), *last);
	}

	iterator Erase(iterator pos)
	{
		iterator tmp = pos;
		++pos;
		Extract(tmp.nd());
		return pos;
	}

	iterator Erase(iterator first, iterator last)
	{ 
		for ( ; first!=last; )
		{
			iterator tmp = first;
			++first;
			Extract(tmp.nd());
		}
		return last;
	}

	void Splice(iterator pos, TList& x)
	{
		TNode *tmp = pos.nd()->next;
		tmp->prev = x.first;
		pos.nd()->next = x.first;
		x.first->prev = pos.nd();
		x.last->prev->next = tmp;
		x.first = 0;
		x.last->next = 0;
		x.last->prev = 0;
	}

	void Splice (iterator pos, TList& x, iterator it)
	{
		TNode *tmp2 = it.nd()->prev;
		TNode *tmp = pos.nd()->next;
		tmp->prev = it.nd();
		pos.nd()->next = it.nd();
		it.nd()->prev = pos.nd();
		x.last->prev->next = tmp;
		tmp->prev = x.last->prev;
		
		x.last->prev = tmp2;
		tmp2->next = x.last;
	}
	
	void Splice (iterator pos, TList& x, iterator first, iterator last)
	{
		TNode *tmp2 = first.nd()->prev;
		TNode *tmp3 = last.nd()->next;
		TNode *tmp = pos.nd()->next;
		tmp->prev = first.nd();
		pos.nd()->next = first.nd();
		it.nd()->prev = pos.nd();
		last.nd()->prev->next = tmp;
		tmp->prev = last.nd()->prev;

		tmp2->next = tmp3;
		tmp3->prev = tmp2;
	}
	T Pop_back()
	{
		T t = last->prev->val;
		TNode *tmp = new TNode (*(last->prev));
		delete last->prev;
		last->prev = tmp->prev;
		tmp->prev->next = last;
		delete tmp;
		return t;
	}
	T Pop_front () 
	{
		T t = first->val;
		first = first->next;
		delete first->prev;
		first->prev = 0;
		return t;
	}
	T& Front ()
	{
		return first->val;
	}
	T& Back () 
	{
		return last->prev->val;
	}
	const T& Front () const
	{
		return first->val;
	}
	const T& Back () const
	{
		return last->prev->val;
	}
	TList& operator= (TList& other)
	{
		if (this!=&other)
		{
			if (!Empty())
				Clear();
			TNode *p = new TNode (other.first->val);
			first = p;
			TNode *c = other.first->next;
			for (; c; c = c -> next, p = p -> next)
			{
				TNode *np = new TNode(c->val, p, 0);
				p -> next = np;
			}
			last = p;
		}
		return *this;
	}

};

template <typename T>
ostream& operator<< (ostream &out, const TFoo<T> &t) 
{
	out << t.Value;
    return out;
};

template <typename T>
void Print(TList <T> &lst)
{
	TList <T>::iterator it=lst.Begin();
    for (; it!=lst.End(); ++it) cout <<' '<<*it;
	cout<<endl;
}

int main()
{
	{
		TList <TFoo<int> > a;
		for (int i=0; i<10; i++) a.Push_back(i);
		cout<<"a: "<<endl;
		Print(a);
		TList <TFoo<int> > b;
		for (int i=0; i<10; i++) b.Push_front(i);
		cout<<"b: "<<endl;
		Print(b);
		TList <TFoo<int> > c(b);
		cout<<"c(b): "<<endl;
		Print(c);
		a.Swap(b);
		cout<<"Swap:"<<endl;
		cout<<"a: "<<endl; Print(a);
		cout<<"b: "<<endl; Print(b);
		a.Pop_back();
		cout<<"a.pop_back(): "<<endl; Print(a);
		a.Pop_front();
		cout<<"a.pop_front(): "<<endl; Print(a);
		a.Insert(++a.Begin(),4);
		cout<<"a.Insert(++a.Begin(),4): "<<endl; Print(a);

		TList<TFoo<int> >::iterator it = a.Begin();
		for (int i=0; i<5; ++i, ++it);
		a.Insert(it, a.Begin(), ++a.Begin());
		cout<<"a.Insert(a.Begin()+5, a.Begin(), a.Begin()+1): "<<endl; Print(a);
		it = a.Begin();
		for (int i=0; i<5; ++i, ++it);
		it = a.Erase(it);
		cout<<"a.Erase(a.Begin()+5): "<<endl; Print(a);
		TList<TFoo<int> >::iterator j = a.End();
		j--;
		it = a.Erase(it, j);
		cout<<"a.Erase(a.Begin()+5, --a.End()): "<<endl; Print(a);
		a.Splice(a.Begin()++, b);
		cout<<"a.Splice(a.Begin()+1, b): "<<endl; Print(a);
		it = c.Begin();
		++it;
		a.Splice(a.Begin(), c, it);
		cout<<"a.Splice(a.Begin(), c, ++c.Begin()): "<<endl; Print(a);
	}
	TFoo<int>::PrintStats();
	return 0;
}
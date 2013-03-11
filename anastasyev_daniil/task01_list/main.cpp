#include <iostream>
#include <list>
using namespace std;

template <typename T>
struct TNode
{
	static int Created, Deleted;
    T val;
    TNode <T> *prev, *next;
    TNode()
    {
        val = 0;
        prev = 0;
        next = 0;
		++Created;
    }
    TNode(T v)
    {
        val = v;
        prev = 0;
        next = 0;
		++Created;
    }
    TNode(T v, TNode *p, TNode *n)
    {
        val = v;
        prev = p;
        next = n;
		++Created;
    }
    ~TNode()
    {    
		++Deleted;
	}
};

template <typename T>
class TIterator
{
    TNode <T> *node;
public:
	TIterator():node(0){}
	TIterator(TNode <T> *t):node(t){}
    T& operator *()
    {
        return node->val;
    }
    TIterator& operator ++()
    {
        node = node->next;
        return *this;
    }
    TIterator& operator --()
    {
		node = node->prev;
        return *this;
    }
    TIterator operator ++(int)
    {
        TIterator it(*this);
        ++(*this);
        return it;
    }
    TIterator operator --(int)
    {
        TIterator it(*this);
        --(*this);
        return it;
    }
    bool operator ==(const TIterator& other)
    {   
        return (node==other.node);
    }
    bool operator !=(const TIterator& other)
    {   
        return (!(*this==other));
    }
	T* operator ->() const
	{
		return (&**this);
	}
	TNode <T>* nd()
	{
		return node;
	}
	TIterator operator+ (int n)
	{
		if (node->next==0)
			return *this;
		for (int i=0; i<n; ++i)
			++*this;
		return *this;
	}
};

template <typename T>
class TList
{
    TNode <T> *first, *last;
public:

	typedef TIterator <T> iterator;
	typedef TNode <T> Node;
    TList()
    {
        first = 0;
        last = 0;
    }
    TList(TList <T> &lst)
    {
        if (lst.first==0) 
        {
            TList();
            return;
        }
        Node *p = new Node (lst.first->val);
        first = p;
        Node *c = lst.first -> next;
		for (; c; c = c -> next, p = p -> next)
        {
            Node *np = new Node(c->val, p, 0);
            p -> next = np;
        }
        last = p;
    }
    ~TList()
    {
        while (first)
        {
            Node *p=first -> next;
            delete first;            
            first = p;
        }
    }
	bool Empty() const
	{
		return (first);
	}
	TIterator <T> Begin()
	{
		return iterator(first);
	}
	TIterator <T> End()
	{
		return iterator(last);
	}
	void Clear()
	{
        while (first)
        {
            Node *p=first -> next;
            delete first;            
            first = p;
        }
		first = 0;
		last = 0;
	}
	void Swap(TList& other)
	{
		swap(*this,other);
	}
	void Push_back(int val)
    {
        Node *p = new Node(val);
        Push_back(p);
    }
    void Push_back(Node *node)
    {
        node -> prev = last;
        if (last != 0)
            last -> next = node;
        else first = node;
        last = node;
    }
    void Push_front(T val)
    {
        Node *p = new Node(val);
		Push_front(p);
    }
    void Push_front(Node *node)
    {
        node -> next = first;
        if (first != 0)
            first -> prev = node;
        else last = node;
        first = node;
    }
    void Insert(Node* where, T val)
    {
        Node *p = new Node(val);
        Insert(where, p);
    }
	void Insert(Node* where, Node* p)
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
	void Insert(iterator pos, T val)
	{
		Insert(pos.nd(), val);
	}
	void Insert(iterator pos, iterator first, iterator last)
	{
		for (; first!=last; --last, --pos)
			Insert(pos.nd(), *last);
	}
	void Extract(Node* p)
	{
		if (p==first && p==last)
		{
			first=0;
			last=0;
			return;
		}
		if (p==first)
			first = p->next;
		else
			p->prev->next = p->next;
		if (p==last)
			last = p->prev;
		else
			p->next->prev = p->prev;
	}
	void Erase(iterator pos)
	{
		Extract(pos.nd());
	}

	void Erase(iterator first, iterator last)
	{ 
		for ( ; first!=last; ++first) Extract(first.nd());
	}

	void Splice(iterator pos, TList& x)
	{
		iterator it=x.End();
		for (; it!=x.Begin(); --pos, --it)
		{
			Insert(pos,*it);
			iterator t=it;
			x.Erase(t);
		}
		Insert(pos,*it);
		x.Erase(it);
	}

	void Splice (iterator pos, TList& x, iterator it)
	{
		Insert(pos,*it);
		x.Erase(it);
	}
	
	void Splice (iterator pos, TList& x, iterator first, iterator last)
	{
		iterator it = --last;
		for (; it!=first; --pos, --it)
		{
			Insert(pos,*it);
			iterator t=it;
			x.Erase(t);
		}
		Insert(pos,*it);
		x.Erase(it);
	}
	T pop_back()
	{
		T t = last->val;
		last = last->prev;
		delete last->next;
		last->next = NULL;
		return t;
	}
	T pop_front () 
	{
		T t = first->val;
		first = first->next;
		delete first->prev;
		first->prev = 0;
		return t;
	}
	T& front ()
	{
		return first->val;
	}
	T& back () 
	{
		return last->prev->val;
	}
	TList& operator= (TList& other)
	{
		if (this!=&other)
		{
			Clear();
			Node *temp = other.first;
			while (temp!=other.last)
			{
				Push_back(temp->val);
				temp = temp->next;
			}
			Push_back(temp->val);
		}
		return *this;
	}

};

int TNode<int>:: Created=0;
int TNode<int>:: Deleted=0;

void Print(TList <int> &lst)
{
	TList <int>::iterator it=lst.Begin();
    for (; it!=lst.End(); ++it) cout <<' '<<*it;
	cout <<' '<<*it<<endl;
}

int main()
{
    TList <int> a;
    for (int i=0; i<10; i++) a.Push_back(i);
	cout<<"a: "<<endl;
	Print(a);
    TList <int> b;
    for (int i=0; i<10; i++) b.Push_front(i);
	cout<<"b: "<<endl;
	Print(b);
	a.Swap(b);
	cout<<"Swap:"<<endl;
	cout<<"a: "<<endl; Print(a);
	cout<<"b: "<<endl; Print(b);
	a.pop_back();
	cout<<"a.pop_back(): "<<endl; Print(a);
	a.pop_front();
	cout<<"a.pop_front(): "<<endl; Print(a);
	a.Insert(a.Begin(),4);
	cout<<"a.Insert(a.Begin(),4): "<<endl; Print(a);
	a.Insert(a.Begin()+5,a.Begin(),a.Begin()+2);
	cout<<"a.Insert(a.Begin()+5,a.Begin(),a.Begin()+2): "<<endl; Print(a);
	a.Erase(a.Begin()+5);
	cout<<"a.Erase(a.Begin()+5): "<<endl; Print(a);
	a.Erase(a.Begin()+5,a.Begin()+7);
	cout<<"a.Erase(a.Begin()+5,a.Begin()+7): "<<endl; Print(a);
	a.Splice(a.Begin()+2,b);
	cout<<"a.Splice(a.Begin()+2,b): "<<endl; Print(a);
	b = a;
	a.Splice(a.Begin()+2,b,b.Begin()+1,b.Begin()+4);
	cout<<"a.Splice(a.Begin()+2,b,b.Begin()+1,b.Begin()+4): "<<endl; Print(a);
	return 0;
    cout <<endl<<TNode<int>::Created<<endl<<TNode<int>::Deleted<<endl;
}
#include <iostream>
#include <list>
using namespace std;

template <typename T>
struct TNode
{
	T value;
	TNode *prev, *next;
	TNode():value(0), prev(0), next(0){}
	TNode(T a):value(a), prev(0), next(0){}
	TNode(T a, TNode *p, TNode* n):value(a), prev(p), next(n) {}
	~TNode(){}
	TNode& operator=(const TNode& a)
	{
		value = a.value;
		prev = a.prev;
		next = a.next;
		return *this;
	}
};
template <typename T>
class TList
{
	struct TNode
	{
		friend class TList;
		T value;
		TNode *prev, *next;
		TNode():value(0), prev(0), next(0){}
		TNode(T a):value(a), prev(0), next(0){}
		TNode(T a, TNode *p, TNode* n):value(a), prev(p), next(n) {}
		~TNode(){}
		TNode& operator=(const TNode& a)
		{
			value = a.value;
			prev = a.prev;
			next = a.next;
			return *this;
		}
	};
	TNode *first, *last;
public:
	class iterator
	{
		friend class TList;
		TNode* Node;
	public:
		iterator():Node(0){}
		iterator(TNode *a):Node(a){}
		iterator& operator++()
		{
			Node = Node->next;
			return *this;
		}
		iterator& operator++(int)
		{
			TNode* help;
			help = help;
			Node = Node->next;
			return iterator(help);
		}
		iterator& operator--()
		{
			Node = Node->prev;
			return *this;
		}
		iterator& operator--(int)
		{
			TNode* help;
			help = help;
			Node = Node->prev;
			return iterator(help);
		}
		T& operator*()
		{
			return Node->value;
		}
		T* operator->()
		{
			return &(Node->value);
		}
		bool operator== (const iterator& a)
		{
			return (Node == a.Node);
		}
		bool operator != (const iterator &a)
		{
			return !(*this == a);
		}
		iterator& operator = (const iterator &a)
		{
			*Node = *(a.Node);
			return *this;
		}
	};
	class const_iterator
	{
		friend class TList;
		TNode* Node;
	public:
		const_iterator():Node(0){}
		const_iterator(TNode *a):Node(a){}
		const_iterator& operator++()
		{
			Node = Node->next;
			return *this;
		}
		const_iterator& operator++(int)
		{
			TNode* help;
			help = help;
			Node = Node->next;
			return const_iterator(help);
		}
		const_iterator& operator--()
		{
			Node = Node->prev;
			return *this;
		}
		const_iterator& operator--(int)
		{
			TNode* help;
			help = help;
			Node = Node->prev;
			return iterator(help);
		}
		const T& operator*() const
		{
			return Node->value;
		}
		const T* operator->() const
		{
			return &(Node->value);
		}
		bool operator== (iterator& a)
		{
			return (Node == a.Node);
		}
		bool operator != (iterator &a)
		{
			return !(*this == a);
		}
		const_iterator& operator = (const iterator &a)
		{
			*Node = *(a.Node);
			return *this;
		}
	};
	TList():first(0), last(0){}
	TList(const TList<T>& l)
	{
        *this = l;
	}
	void clear()
	{
	    for (;(first != 0);)
        {

            TNode *help = first->next;
            delete first;
            first = help;
        }
        first = last = 0;
	}
	bool empty () const
	{
        return first == 0;
	}
	void push_front(const T& a)
	{
	    TNode *help = new TNode(a);
	    help->next = first;
	    if (last == 0)
            last = help;
		else
		{
            first->prev = help;
        }
        first = help;

	}
	void pop_front()
	{
	    TNode *help = first;
	    first = first->next;
	    first->prev = 0;
	    delete help;
	}

	void push_back(const T& a)
	{
	    TNode *help = new TNode(a);
	    help->prev = last;
	    if (first == 0)
            first = help;
        else
            last->next = help;
        last = help;
    }
	void pop_back()
	{
	    TNode *help = last;
	    last = last->prev;
	    last->next = 0;
	    delete help;
	}
	T& front ()
	{
	    return (first->value);
	}
	T& back()
	{
	    return (last->value);
	}
	const T& front ()const
	{
	    return (first->value);
	}
	const  T& back() const
	{
	    return (last->value);
	}
	TList& operator = (const TList& l)
	{
	    clear();
	    first = last = 0;
	    TNode* help;
	    help = l.first;
	    for (;help != l.last;)
        {
            push_back(help->value);
            help = help->next;
        }
        push_back(help->value);
        return *this;
	}
	void swap(TList& l)
	{
	    std::swap(first, l.first);
	    std::swap(last, l.last);
	}
	iterator insert(iterator in, T a)
	{
	    TNode* help = new TNode(a, in.Node->prev, in.Node);
	    in.Node->prev->next = help;
	    in.Node->prev = help;
		return (help);
	}
	void insert(iterator in, size_t n, T a)
	{
        for (size_t i = 0; i < n; ++i)
            insert(in, a);
	}
	iterator erase(iterator what)
	{
	    TNode* help = what.Node;
	    what.Node->prev->next = what.Node->next;
	    what.Node->next->prev = what.Node->prev;
	    ++what;
		delete help;
	    return what;
	}
	iterator erase (iterator first, iterator last)
	{
	    for (;first != last;)
        {
            first = erase(first);
        }
        return last;
	}
	iterator begin()
	{
	    return iterator(first);
	}
	iterator end()
	{
	    return (iterator(last->next));
	}
	const_iterator begin()const
	{
	    return iterator(first);
	}
	const_iterator end()const
	{
	    return (iterator(last->next));
	}
	void splice(iterator in, TList& x)
	{
	    if (in.Node == 0)
		{
			last->next = x.first;
			x.first->prev = last;
			last = x.last;
			
		}
		else if (in == begin())
		{
			first->prev = x.last;
			x.last->next = first;
			first = x.first;
		}
		else
		{
		TNode* help = in.Node->prev;
	    help->next = x.first;
	    x.first->prev = help;
	    x.last->next = in.Node;
	    in.Node->prev = x.last;
		}
		x.first = x.last = 0;
	}
	void splice(iterator in, TList& x, iterator i)
	{
	    insert(in, *i);
		x.erase(i);
	}
	~TList()
	{
		clear();
	}


};
template <typename T>
void print(TList<T> &l)
{
    for (typename TList<T>::iterator it = l.begin();
		it != (l.end()); 
		++it)
        cout << *it << ' ';
    cout << endl;
}
struct myint
{
        size_t x;
        static int Created;
        static int Deleted;
        myint()
        {
                ++Created;
                x = 0;
        }
        myint(const myint &a)
        {
                ++Created;
                x = a.x;
        }
        ~myint()
        {
                ++Deleted;
        
        }
                myint operator+(myint a)
                {
                        myint b;
                        b.x = a.x + x ;
                        return b;
                }
                myint& operator+=(myint a)
                {
                        x += a.x;
                        return *this;
                }
};
int myint::Created = 0;
int myint::Deleted = 0;
int main()
{
    TList<int> a;
    for (int i = 0; i < 10; ++i)
        a.push_back(i);
    cout << "New TList<int> a: " << endl;
	print(a);
	TList<int> b;
	for (int i = 19; i >=10; --i)
		b.push_front(i);
	cout << "New TList<int> b:" << endl;
	print(b);
	a.splice(a.begin(), b);
	cout << "a.splice(a.begin(), b)" << endl;
	print(a);
	TList<int> c;
	for (int i = 29; i>=20; --i)
		c.push_back(i);
	cout << "New TList<int> c:" << endl;
	print(c);
	a.swap(c);
	cout << "a.swap(c)" << endl;
	cout << "a: ";
	print(a);
	cout << "c: ";
	print(c);
	cout <<"TList<int>::iterator it = a.insert(++a.begin(), 100);" << endl;
	TList<int>::iterator it = a.insert(++a.begin(), 100);
	print(a);
	a.erase(it);
	cout << "a.erase(it)"<< endl;
	print(a);
	cout << "Check memory" << endl;
	{
		TList<myint> abc, bcd;
		myint t;
		for (int i = 0; i < 20; ++i)
		{
			t.x = i;
			abc.push_back(t);
			bcd.push_front(t);
		}
		abc.splice(abc.begin(), bcd);
		
	}
	cout << myint::Created << ' ' << myint::Deleted;
	return 0;
}

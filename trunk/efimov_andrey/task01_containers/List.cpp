#include <iostream>
#include <list>
using namespace std;

template <typename T>
struct TNode{
	static int Created, Deleted;
	T val;
	TNode <T> *prev, *next;
	TNode(){
		val = 0;
		prev = 0;
		next = 0;
		++Created;
	}
	TNode(T v){
		val = v;
		prev = 0;
	next = 0;
	++Created;
	}
	TNode(T v, TNode *p, TNode *n){
		val = v;
		prev = p;
		next = n;
		++Created;
	}
    ~TNode(){
		++Deleted;
	}
};

template <typename T>
class TIterator{
    TNode<T>* node;
public:
	TIterator():node(0){}
	TIterator(TNode <T> *t):node(t){}
    T& operator* (){
        return node->val;
    }
    TIterator& operator++ (){
        node = node->next;
        return *this;
    }
    TIterator& operator-- (){
		node = node->prev;
		return *this;
	}
	TIterator operator++ (int){
        TIterator it(*this);
		++(*this);
		return it;
	}
    TIterator operator-- (int){
		TIterator it(*this);
		--(*this);
		return it;
	}
	bool operator== (const TIterator& other){   
		return (node==other.node);
	}
	bool operator!= (const TIterator& other){   
		return (!(*this==other));
    }
	T* operator->() const{
		return (&**this);
	}
	TNode<T>* nd(){
		return node;
	}
	TIterator operator+ (int n){
		if (node->next==0)
			return *this;
		for (int i=0; i<n; ++i)
			++*this;
		return *this;
	}
};

template <typename T>
class TList{
	TNode <T> *first, *last;
public:
	typedef TIterator<T> Iterator;
	typedef TNode<T> Node;
    TList(){
		first=0;
		last=0;
	}
    TList(TList<T> &lst){
		if (lst.first==0){
			TList();
			return;
		}
		Node *p = new Node (lst.first->val);
		first=p;
		Node *c = lst.first -> next;
		for (; c; c = c->next, p = p->next){
			Node *np = new Node(c->val, p, 0);
			p->next = np;
		}
		last = p;
	}
    ~TList(){
		while (first){
			Node *p=first->next;
			delete first;            
			first=p;
        }
    }
	bool Empty() const{
		return (first);
	}
	TIterator<T> Begin(){
		return Iterator(first);
	}
	TIterator<T> End(){
		return Iterator(last);
	}
	void Clear(){
		while (first){
		Node *p=first -> next;
			delete first;            
			first=p;
		}
		first=0;
		last=0;
	}
	void swap(TList& other){
		TNode<T>* temp;
		temp=this->first;
		this->first=other.first;
		other.first=temp;
		temp=this->last;
		this->last=other.last;
		other.last=temp;
	}
	void push_back(int val){
		Node *p = new Node(val);
		push_back(p);
	}
    void push_back(Node *node){
		node->prev = last;
		if (last!=0)
		last->next = node;
	else first=node;
		last=node;
	}
    void push_front(T val){
		Node *p = new Node(val);
		push_front(p);
	}
    void push_front(Node *node){
		node->next = first;
		if (first!=0)
			first->prev = node;
		else last=node;
        first=node;
    }
    void Insert(Node* where, T val){
        Node *p = new Node(val);
        Insert(where, p);
	}
	void Insert(Node* where, Node* p){
		if (where==first){
			push_front(p->val);
			delete p;
		}
		else{
			p->prev = where->prev;
			p->next = where;
			where->prev->next = p;
			where->prev = p;
		}	
	}
	void Insert(Iterator pos, T val){
		Insert(pos.nd(), val);
	}
	void Insert(Iterator pos, Iterator first, Iterator last){
		for (; first!=last; --last, --pos)
			Insert(pos.nd(), *last);
	}
	void Extract(Node* p){
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
	Iterator Erase(Iterator pos){
		Iterator tmp = pos;
		++pos;
		Extract(tmp.nd());
		return pos;
	}
	Iterator Erase(Iterator first, Iterator last){ 
		for ( ; first!=last; ){
			Iterator tmp = first;
			++first;
			Extract(tmp.nd());
		}
		return last;
	}
	void Splice(Iterator pos, TList& x){
		Node *tmp = pos.nd()->next;
		tmp->prev = x.first;
		pos.nd()->next = x.first;
		x.first->prev = pos.nd();
		x.last->next = tmp;
		x.first = 0;
		x.last->next = 0;
		x.last->prev = 0;
	}
	void Splice (Iterator pos, TList& x, Iterator it){
		Node *tmp2 = it.nd()->prev;
		Node *tmp = pos.nd()->next;
		tmp->prev = it.nd();
		pos.nd()->next = it.nd();
		it.nd()->prev = pos.nd();
		x.last->prev->next = tmp;
		tmp->prev = x.last->prev;
		x.last->prev = tmp2;
		tmp2->next = x.last;
	}
	void Splice (Iterator pos, TList& x, Iterator first, Iterator last){
		Node *tmp2 = first.nd()->prev;
		Node *tmp3 = last.nd()->next;
		Node *tmp = pos.nd()->next;
		tmp->prev = first.nd();
		pos.nd()->next = first.nd();
		first.nd()->prev = pos.nd();
		last.nd()->next = tmp;
		tmp->prev = last.nd()->prev;
		tmp2->next = tmp3;
		tmp3->prev = tmp2;
	}
	T pop_back(){
		T t = last->val;
		last = last->prev;
		delete last->next;
		last->next = NULL;
		return t;
	}
	T pop_front(){
		T t = first->val;
		first = first->next;
		delete first->prev;
		first->prev = 0;
		return t;
	}
	T& front(){
		return first->val;
	}
	T& back() {
		return last->prev->val;
	}
	TList& operator= (TList& other){
		if (this!=&other){
			Clear();
			Node *temp = other.first;
			while (temp!=other.last){
				push_back(temp->val);
				temp = temp->next;
			}
			push_back(temp->val);
		}
		return *this;
	}
};



void Print(TList <int> &lst){
	TList <int>::Iterator it=lst.Begin();
	for (; it!=lst.End(); ++it) cout << ' ' << *it;
	cout << ' ' << *it << endl;
}

template <>
int TNode<int>:: Created=0;
template <>
int	TNode<int>:: Deleted=0;

void MoreTestingRequired(){
	TList<int> a;
	TList<int> b;
	for (int i=0; i<40; ++i){
		a.push_back(i);
		b.push_front(i);
	}
	{
		cout << "a: ";
		Print(a);
		cout << "b: ";
		Print(b);
		cout << "Popback for both" << endl;
		a.pop_back();
		b.pop_back();
		cout << "a: ";
		Print(a);
		cout << "b: ";
		Print(b);
		cout << "Now for the front" << endl;
		a.pop_front();
		b.pop_front();
		cout << "a: ";
		Print(a);
		cout << "b: ";
		Print(b);
		cout << "Swhap" << endl;
		a.swap(b);
		cout << "a: ";
		Print(a);
		cout << "b: ";
		Print(b);
		cout << "INSERTIONNN" << endl;
		a.Insert(a.Begin()+2, 9);
		b.Insert(b.Begin()+2, 0);
		cout << "a: ";
		Print(a);
		cout << "b: ";
		Print(b);
		cout << "More insertion!" << endl;
		a.Insert(a.Begin()+2, b.Begin()+5, b.Begin()+8);
		b.Insert(b.Begin()+2, a.Begin()+8, a.Begin()+11);
		cout << "a: ";
		Print(a);
		cout << "b: ";
		Print(b);
		cout << "Destroy the lesser middle nodes!" << endl;
		a.Erase(a.Begin()+7);
		b.Erase(b.Begin()+6, b.Begin()+8);
		cout << "a: ";
		Print(a);
		cout << "b: ";
		Print(b);
		cout << "Tear it up!" << endl;
		a.Splice(a.Begin()+2, b, b.Begin()+4, b.Begin()+7);
		cout << "a: ";
		Print(a);
		cout << "b: ";
		Print(b);
		system("pause");
	}
	cout << ((TNode<int>::Created-TNode<int>::Deleted==0)?"All Fine":"Red Alert");
	system("pause");
}

int main(){
	MoreTestingRequired();
	return 0;
}
#include <iostream>
#include <vector>
using namespace std;


struct TFoo {
    int Value;
    TFoo() : Value(0) { ++Created; }
    TFoo(const TFoo &other) : Value(other.Value) { ++Created; }
    ~TFoo() { ++Deleted; }
    bool operator< (const TFoo& other)
    {
        return Value < other.Value;
    }

	bool operator< (const TFoo& other) const 
    {
        return Value < other.Value;
    }
    bool operator<= (const TFoo& other)
    {
        return Value <= other.Value;
    }
    static int Created;
    static int Deleted;
    static void PrintStats() {
        cout << "TFoo::Created = " << Created << endl
            << "TFoo::Deleted = " << Deleted << endl;
    }
	bool operator== (const TFoo& a){
		return ( Value == a.Value);
	}
};


int TFoo::Created = 0;
int TFoo::Deleted = 0;

template <typename T>
class TList{
	struct node{
		friend class TList;
		node(T& a): val(a){
		}
		node(){
			prev=0;
			next=0;
		}

		~node(){
		}
		T val;
		node* next;
		node* prev;
		bool operator== (node& another){
			return (val == another.val && next == another.next && prev == another.prev);
		}
		bool operator!= (node& another){
			return !(*this == another);
		}
	};
	node* first;
	node* last;
	node* limit;
public:
	class iterator{
		friend class TList;
	public:
		iterator(node *t):el(t){}
		iterator():el(0){
		};

		void operator++(){
			el=el->next;
		};

		void operator --(){
			el=el->prev;
		}

		T operator *(){
			return el->val;;
		}

		bool operator == (iterator& i){
			return (el == i.el ? true:false);
		}

		bool operator != (iterator& i){
			return !(*this == i);
		}

		void operator=(iterator tp){
			el=tp.get();
			return;
		}

		node* get(){
			return el;
		}

		bool Last(){
			if (el->next==0)
				return true;
			return false;
		}

		bool First (){
			if (el->prev==0)
				return true;
			return false;
		}

		iterator operator+(int n){
			if (el->next==0)
				return *this;
			for (int i=0; i<n; ++i)
				++*this;
			return *this;
		}

	private:
		node* el;
	};

	class const_iterator{
		friend class TList;
	public:
		const_iterator(node *t):el(t){}
		const_iterator():el(0){
		};

		void operator++(){
			el=el->next;
		};

		void operator --(){
			el=el->prev;
		}

		const T& operator *() const{
			return el->val;;
		}

		bool operator == (const_iterator& i){
			return (el == i.el ? true:false);
		}

		bool operator != (const_iterator& i){
			return !(*this == i);
		}

		void operator=(const_iterator tp){
			el=tp.get();
			return;
		}

		node* get(){
			return el;
		}

		bool Last(){
			if (el->next==0)
				return true;
			return false;
		}

		bool First (){
			if (el->prev==0)
				return true;
			return false;
		}

		const_iterator operator+(int n){
			if (el->next==0)
				return *this;
			for (int i=0; i<n; ++i)
				++*this;
			return *this;
		}

	private:
		node* el;
	};
private:
	void Insert(node* where, T val){
		node* n=new node;
		n->val=val;
		Insert(where,n);
	};

	void Insert(node* where, node* tnode){
		if (where==first){
			push_front(tnode->val);
			delete tnode;
		}
		else {
			tnode->prev=where->prev;
			tnode->next=where;
			where->prev->next=tnode;
			where->prev=tnode;
		}	
	};	

	void Insert(node* where, TList &other){
		if (where->prev!=0){
			(where->prev)->next=other.first;
			other.first->prev=where->prev;
			where->prev=other.last;
			other.last->next=where;
			other.first=0;
			other.last=0;
		}
		else{
			first=other.first;
			where->prev=other.last;
			other.last->next=where;
			other.first=0;
			other.last=0;
		}
	};

	void Extract(node* tnode){
		if(tnode==first && tnode==last){
			first=0;
			last=0;
			delete tnode;
			return;
		}
		if(tnode==first)
			first=tnode->next;
		else
			tnode->prev->next=tnode->next;
		if(tnode==last)
			last=tnode->prev;
		else
			tnode->next->prev=tnode->prev;
		delete tnode;
		return;
	};

	void Extract(node* tnode, iterator beg){
		if(tnode==first && tnode==last){
			first=0;
			last=0;
			delete tnode;
			return;
		}
		++beg;
		if(tnode==first)
			first=tnode->next;
		else
			tnode->prev->next=tnode->next;
		if(tnode==last)
			last=tnode->next;
		else
			tnode->next->prev=tnode->prev;
		delete tnode;
		return;
	};


public:
	TList(){
		first=last=0;
		limit = new node;
		limit->next = 0;
		limit-> prev = 0;
	}

	TList ( TList<T>& another){
		*this = another;
	}

	TList (T val, int n){
		first=last=0;
		limit = new node;
		limit->next = 0;
		limit-> prev = 0;
		for(int i=0; i<n; ++i)
			push_back(val);
	}

	~TList(){
		clear();
		delete limit;
	}

	iterator begin(){
		return iterator(first);
	}

	iterator end (){
		return iterator(limit);
	}

	const_iterator cbegin(){
		return const_iterator(first);
	}

	const_iterator cend (){
		return const_iterator(limit);
	}

	bool empty () const {
		return first==0? true:false;
	}

	void clear (){
		while( first != 0 && *first != *limit ){
			last=first->next;
			delete first;
			first=last;
		}
		first=last=0;
	}

	void push_back (T val) {
		node* tp=new node;
		tp->val=val;
		tp->next=limit;
		if(first==0){
			tp->prev=limit;
			limit->prev = tp;
			first=last=tp;	
		}
		else {
			tp->prev=last;
			last->next=tp;
			last=tp;
			limit->prev = tp;
		}
	}

	void push_front(T val){
		node* tp=new node;
		tp->val=val;
		tp->prev=limit;
		if (last==0)
		{last=first=tp;
		tp->next=limit;
		}
		else{
			tp->next=first;
			first->prev=tp;
			first=tp;
		}
		return;
	}

	T pop_back(){
		T tp=last->val;
		last=last->prev;
		delete last->next;
		last->next=limit;
		limit->prev = last;
		return tp;
	}

	T pop_front () {
		T tp=first->val;
		first=first->next;
		delete first->prev;
		first->prev=limit;
		return tp;
	}

	T& front (){
		return first->val;
	}

	T& back () {
		return last->val;
	}

	TList& operator=( TList &other){
		if(this!=&other){
			clear();
			first=0;
			last=0;
			node* temp;
			temp=other.first;
			while(temp!=other.last){
				push_back(temp->val);
				temp=temp->next;
			}
			push_back(temp->val);
		}
		return *this;
	};

	void swap(TList& temp){
		TList tp;
		tp=*this;
		*this=temp;
		temp=tp;
		return;
	}
	


	void insert(iterator pos, T val){
		Insert(pos.get(),val);
		return;
	}

	void insert (iterator pos, int n, T val){
		for (int i=0; i<n; i++)
			Insert(pos.get(), val);
		return;
	}

	void insert (iterator pos, iterator beg, iterator end){
		--end;
		for (; beg!=end; --end, --pos)
			Insert(pos.get(), *end);
		Insert(pos.get(), *end);
		return;
	}

	
	iterator erase(iterator pos){
		Extract(pos.get(), pos);
		return pos;
	}

	iterator erase (iterator beg, iterator end){ 
		for (;beg!=end;){
			iterator tp=beg;
			++beg;
			Extract(tp.get());
		}
		return end;
	}

	void splice (iterator pos, TList& lt){
		iterator tp=lt.end();
		iterator beg=lt.begin();
		--tp;
		for (; tp!=beg; --pos){
			insert(pos,*tp);
			iterator t=tp;
			--tp;
			lt.erase(t);
		}
		insert(pos,*tp);
		lt.erase(tp);
		return;
	}

	void splice (iterator pos, TList& lt, iterator it){
		insert(pos,*it);
		lt.erase(it);
		return;
	}
	
	void splice (iterator pos, TList& lt, iterator first, iterator last){
		iterator tp=last;
		--tp;
		for (; tp!=first; --pos){
			insert(pos,*tp);
			iterator t=tp;
			--tp;
			lt.erase(t);
		}
		insert(pos,*tp);
		lt.erase(tp);
		return;
	}
};


template <typename T>
void show (TList<T>& a){
		auto pos = a.cbegin();
		if (!a.empty())
			for (int i=1; pos != a.cend(); ++pos, i++ )
				cout << "Element "<<i<< " : "<< (*pos).Value <<endl;
		cout <<"________________________________________________"<<endl;
	};

int main(){
	{TList <TFoo> a,b;
	TList<TFoo> aa;
	TList<TFoo>  bb;
	show(bb);
	for (int i=0; i<10; i++){
		TFoo temp;
		temp.Value = i;
		a.push_back(temp);
	}
	for (int i=0; i<10; i++){
		TFoo temp;
		temp.Value = i;
		b.push_front(temp);
	}
	if (a.empty())
	cout <<"true\n";
	else 
	cout << "false\n";
	b=a;
	show(b);
	a.swap(b);
	show(a);
	show(b);
	TFoo p;
	show(b);
	for (int i=0; i<5; i++)
		p=a.pop_front();
	show(a);
	a.clear();
	if (a.empty())
	cout <<"true\n";
	else 
	cout << "false\n";
	show(a);
	TFoo temp;
	temp.Value = 20;
	a.insert(a.begin(), temp);
	show(a);
	a.insert(a.begin(), 2, temp);
	show(a);
	a.insert(a.begin(), b.begin(), b.end());
	show(a);
	show(a);
	a.erase(a.begin()+1);
	show(a);
	a.erase(a.begin()+3, a.end());
	show(a);
	a.splice(a.begin()+1, b);
	show(a);
	b.splice(b.begin(), a, a.begin()+3);
	show(b);
	show(a);
	b.splice(b.begin(), a, a.begin()+3, a.begin()+6);
	show(b);
	show(a);}
	TFoo :: PrintStats();
	return 0;
}
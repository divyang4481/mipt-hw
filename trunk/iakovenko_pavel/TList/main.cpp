#include <iostream>
#include <vector>
using namespace std;
// Должна ли возвращать erase какой-то оператор?

template <typename T>
class TList{
	struct node{};
public:
	class iterator{
		friend class TList;
		iterator(node *t):el(t){}
	public:
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
public:
	TList(){
		first=last=0;
		rehersal();
	}

	TList (T val){
		node* t=new node;
		t->val=val;
		t->prev=t->next=0;
		first=last=t;
		rehersal();
	}

	void rehersal(){
		Begin=iterator(first);
		End=iterator(last);
	}

	~TList(){
		while(first){
		last=first->next;
		delete first;
		first=last;
	}
	}

	iterator begin(){
		Begin=iterator(first);
		return Begin;
	}

	iterator end (){
		End=iterator(last);
		return End;
	}

	bool empty (){
		return first==0? true:false;
	}

	void clear (){
		while(first){
		last=first->next;
		delete first;
		first=last;
	}
		first=last=0;
	}

	void push_back (T val) {
		node* tp=new node;
		tp->val=val;
		tp->next=0;
		if(first==0)
		{tp->prev=0;
		first=last=tp;	
		}
		else {
			tp->prev=last;
			last->next=tp;
			last=tp;
		}
	}

	void push_front(T val){
		node* tp=new node;
		tp->val=val;
		tp->prev=0;
		if (last==0)
		{last=first=tp;
		tp->next=0;
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
		last->next=0;
		return tp;
	}

	T pop_front () {
		T tp=first->val;
		first=first->next;
		delete first->prev;
		first->prev=0;
		return tp;
	}

	T& front (){
		if (first!=0)
			cout <<"Error!"<<endl;
		return first->val;
	}

	T& back () {
		if (last!=0)
			cout <<"Error!"<<endl;
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
		if (!end.Last())
			--end;
		for (; beg!=end; --end, --pos)
			Insert(pos.get(), *end);
		Insert(pos.get(), *end);
		return;
	}

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

	void erase(iterator pos){
		Extract(pos.get());
		return;
	}

	void erase (iterator beg, iterator end){ //бег просидяет. Не переходит на следующий элемент.
		for (;beg!=end;){
			iterator tp=beg;
			++beg;
			Extract(tp.get());
		}
		if (end.get()==last)
			Extract(end.get());
		return;
	}

	void splice (iterator pos, TList& lt){
		iterator tp=lt.end();
		for (; tp!=lt.begin(); --pos){
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
		if (tp.get()!=lt.last)
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



	void show (){
		node* temp=first;
		for (int i=1; temp!=0; temp=temp->next, i++ )
			cout << "Element "<<i<< " : "<< temp->val <<endl;
		cout <<"________________________________________________"<<endl;
	};

	static int Created;
	static int Deleted;
private:
	struct node{
		friend class TList;
		node(T& a): val(a){
		}
		node(){
			prev=0;
			next=0;
			val=0;
			++Created;
		}
		~node(){
			++Deleted;
		}
		T val;
		node* next;
		node* prev;
	};
	node* first;
	node* last;
	iterator Begin;
	iterator End;
};

int TList<int>:: Created=0;
int TList<int>:: Deleted=0;

int main(){
	{TList <int> a,b;
	for (int i=0; i<10; i++)
		a.push_back(i);
	for (int i=0; i<10; i++)
		b.push_front(i);
	if (a.empty())
	cout <<"true\n";
	else 
	cout << "false\n";
	b=a;
	b.show();
	a.swap(b);
	a.show();
	b.show();
	int p;
	b.show();
	for (int i=0; i<5; i++)
		p=a.pop_front();
	a.show();
	a.front() -= a.back();
	cout << "mylist.front() is now " << a.front() << '\n';
	a.clear();
	if (a.empty())
	cout <<"true\n";
	else 
	cout << "false\n";
	a.show();
	a.insert(a.begin(), 20);
	a.show();
	a.insert(a.begin(), 2, 100);
	a.show();
	a.insert(a.begin(), b.begin(), b.end());
	a.show();
	a.show();
	a.erase(a.begin()+1);
	a.show();
	a.erase(a.begin()+3, a.end());
	a.show();
	a.splice(a.begin()+1, b);
	a.show();
	b.splice(b.begin(), a, a.begin()+3);
	b.show();
	a.show();
	b.splice(b.begin(), a, a.begin()+3, a.begin()+6);
	b.show();
	a.show();}
	cout << TList<int>::Created<<endl<<TList<int>::Deleted<<endl;
	system("pause");
	return 0;
}
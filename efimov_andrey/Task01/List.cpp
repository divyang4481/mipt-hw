#include <iostream>
#include <list>

using namespace std;

template <typename T>
	struct TNode{
		T val;
		TNode<T> *prev, *next;
		TNode(){
			prev=0;
			next=0;
			val=0;
		}
		TNode(T n){
			prev=0;
			next=0;
			val=n;
		}
		TNode(T n, TNode* prev, TNode* next){
			val=n;
			prev=prev;
			next=next;
		}
	};
template <typename T>
	class TIter{
		TNode<T>* node;
	public:
		TIter():node(0){}
		TIter(TNode <T> *t):node(t){}
	T& operator *(){
		return node->val;
		}
	TIter operator ++(){
		node = node->next;
		return this;
	}
	TIter operator --(){
		node = node->prev;
		return this;
	}
	TIter operator ++(int){
		TIter it(*this);
		++(*this);
		return it;
    }
    TIter operator --(int){
		TIterator it(*this);
		--(*this);
		return it;
    }
    bool operator ==(const TIter& other){
		return (node==other.node);
	}
	bool operator !=(const TIter& other){   
		return (!(*this==other));
	}
	T* operator ->() const{
		return (&**this);
	}
	TNode <T>* GetNode(){
		return node;
	}
	TIter operator+ (int n){
		for (int i=0; i<n; ++i){
			if (node->next==0)
				return this;
			++this;
		}
		return this;
	}
};

template <typename T>
class TList{
	typedef TNode<T> node;
	typedef TIter<T> iterator;
private:
	node* first;
	node* last;
public:
	TList(){
			first=0;
			last=0;
		}
	TList(node* left, node* right){
			first=l;
			last=r;
		}
	TList(const TList<T> &a){
			if (a.first !=0){
				TNode* pre=new TNode(a.first->val);
				first=pre;
				TNode* cur=a.first->next;
				for(; cur; cur=cur->next, pre=prev->next){
					TNode *newn=new TNode (cur->val, p, 0);
					pre->next=newn;
				}
				last=pre;
			}
			else{
				TList();
				return;
			}
		}
	~TList(){
			node* cur;
			for (;first;first=cur){
				cur=first->next;
				delete first;
			}
		}
	bool empty(){
			return (first==0)?1:0;
		}
	void clear(){
			TNode* cur;
			for (;first;first=cur){
				cur=first->next;
				delete first;
			}
			first=0;
			last=0;
		}
	void swap(TList<T>& other){
			swap(*this,other);
		}
	iterator begin(){
			return iterator(first);
		}
	iterator end(){
			return iterator(last);
		}
	T& front (){
			return first->val;
		}
	T& back (){
			return last->prev->val;
		}	
	node* push_front(int v){
		TNode *p;
		p=insert (first, v);
		return p;
	}
	void push_front(node* p){
		insert (first, p);
	}
	node* push_back (int v){
		TNode *p = new TNode(v);
		Pushback (p);
		return p;
	}
	void push_back (node* p){
		p->prev = last;
		if (last!=0){
			last->next = p;
		}
		else{
			first=p;
		}
		last=p;
	}
	T pop_front(){
		T v = first->val;
		first=first->next;
		delete first->prev;
		first->prev=0;
	}
	T pop_back(){
		T v = last->val;
		last=last->prev;
		delete last->next;
		last->next=0;
	}
	node* insert(node* pos, int v){
		TNode* p = new TNode(v);
		Insert (pos, p);
		return p;
	}
	void insert(node* pos, node* what){
		if (first==0){
			first=what;
			last= what;
			return;
		}
		if (first==pos){
			first = what;
		}
		else{
			what->prev = pos->prev;
			what->prev->next = what;
		}
		what->next = pos;
		pos->prev = what;
		return;
	}
	void insert(iterator pos, T val){
		Insert(pos.GetNode(), val);
	}
	void insert(iterator pos, iterator start, iterator finish){
		for (; start!=finish; --finish, --pos)
			Insert(pos.GetNode(), *finish);
	}
	void splice(iterator pos, TList& that){
		iterator it=that.end();
		for (; it!=that.begin(); --pos, --it)
		{
			insert(pos,*it);
			that.erase(it);
		}
		insert(pos,*that.begin);
		that.Erase(that.begin);
	}
	void splice (iterator pos, TList& that, iterator it){
		insert(pos,*it);
		that.erase(it);
	}
	void splice (iterator pos, TList& that, iterator start, iterator finish){
		for (iterator cur=finish, cur!=start; cur--)
			splice(pos, that, cur);
	}
	void erase (iterator it){
			n=it.GetNode();
			if (n->prev!=0) n->prev->next=n->next;
			if (n->next!=0) n->next->prev=n->prev;
			if (n==first) first=n->next;
			if (n==last) last=n->prev;
		}
	void erase (iterator il, iterator ir){
			for (;il!=ir; il++) erase(il);
		}
	bool operator= (TList& other){
		if (this!=&other)
		{
			clear();
			node *temp = other.first;
			while (temp!=other.last)
			{
				push_back(temp->val);
				temp = temp->next;
			}
			push_back(temp->val);
		}
		return *this;
	}
};

int main(){
};
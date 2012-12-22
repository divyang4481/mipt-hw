#include <iostream>
using namespace std;

int Created = 0;
int Deleted = 0;

struct TNode{
	int value;
	TNode *next, *prev;
	TNode(){
            ++Created;
		prev=0;
		next=0;
		value=0;
	};
	explicit TNode(int a){
            ++Created;
		value=a;
		prev=0;
		next=0;
	};
	TNode(int a, TNode *p, TNode *n){
            ++Created;
		value=a;
		prev=p;
		next=n;
	};
	~TNode(){
            ++Deleted;
	};

};

class TList{
public: 
	TNode* first;
	TNode* last;

public:
TList(){
	first=0;
	last=0;
};

TList(const TList& other){
	*this=other;
};

TList& operator=(const TList &other){
	if(this!=&other){
		first=0;
		last=0;
		TNode* temp;
		temp=other.first;
		while(temp!=other.last){
			PushBack(temp->value);
			temp=temp->next;
		}
		PushBack(temp->value);
	}
	return *this;
};

~TList(){
	while(first){
		last=first->next;
		delete first;
		first=last;
	}
};

bool IsEmpty() const{
	return (first==0)? true: false;
};

int First() const{
	return first->value;
};
 
int Last() const{
	return last->value;
};

const TNode* FirstNode() const{
	return first;
};
TNode* FirstNode(){
	return first;
};

const TNode* LastNode() const{
	return last;
};
TNode* LastNode(){
	return last;
};

void PushBack(int val){
	TNode* n=new TNode;
	n->value=val;
	PushBack(n);
};

void PushBack(TNode* node){
	node->next=0;
	if(first==0)
	{node->prev=0;
	first=last=node;	
	}
	else {
	node->prev=last;
	last->next=node;
	last=node;
	}
};

void PushFront(int val){
	TNode* n=new TNode;
	n->value=val;
	PushFront(n);
};

void PushFront(TNode* node){
	node->prev=0;
	if (last==0)
	{last=first=node;
	node->next=0;
	}
	else{
		node->next=first;
		first->prev=node;
		first=node;
	}
};

void Insert(TNode* where, int val){
	TNode* n=new TNode;
	n->value=val;
	Insert(where,n);
};

void Insert(TNode* where, TNode* node){
	if (where==first){
		PushFront(node);
	}
	else {
		node->prev=where->prev;
		node->next=where;
		where->prev->next=node;
		where->prev=node;
	}	
};	

void Insert(TNode* where, TList &other){
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

int PopLast(){
	int temp=last->value;
	last=last->prev;	
	free(last->next);
	last->next=0;
	return temp;
};

int PopFirst(){
	int temp=first->value;
	first=first->next;
	free(first->prev);
	first->prev=0;
	return temp;
};

void Delete(const TNode* node){
	if(node==first && node==last){
		first=last=0;
		delete node;
		return;
	}
	if(node->prev==0){
		first=node->next;
		delete node;;
		first->prev=0;
	}
	else if (node->next==0){
		last=node->prev;
		delete node;
		last->next=0;
	}
	else {
		node->next->prev=node->prev;
		node->prev->next=node->next;
		delete node;
	}	

};

void Delete(TNode* from, TNode *to){
		while(from!=to){
			from=from->next;
			Delete(from->prev);
		}
		Delete(to);
};

TNode* ExtractLast(){
	return Extract(last);
};	

TNode* ExtractFirst(){
	return Extract(first);
};

TNode* Extract(TNode* node){
	TNode* temp=node;
	if(node==first && node==last){
		first=0;
		last=0;
		first->next=0;
		last->prev=0;
		return temp;
	}
	if(node==first)
		first=node->next;
	else
		node->prev->next=node->next;
	if(node==last)
		last=node->next;
	else
		node->next->prev=node->prev;
	return temp;
};

TList Extract(TNode* from, TNode* to){
	TList temp;
	if (from==first && to==last){
		first=last=0;
	}
	if(from==first)
		to->next->prev=0;
	else
		to->next->prev=from->prev;
	if(to==last)
		from->prev->next=0;
	else
		from->prev->next=to->next;
	while (from!=to){
		temp.PushBack(from->value);
		from=from->next;
		delete from->prev;
	}
	temp.PushBack(to);
	return temp;
};

void show (){
	TNode* temp=first;
	while(temp!=0){
		cout << temp->value <<" ";
		temp=temp->next;
	}
	cout << endl;
};
};

int main(){
    {
	TList a,b;
	for (int i=0; i<10; i++)
		a.PushFront(i);
	for (int i=0; i<10; i++)
		a.PushBack(i);
	a.show();
	cout << a.PopLast()<< endl;
	a.show();
	for (int i=0; i<10; i++)
		a.PushFront(i);
	a.show();
	cout << a.PopFirst()<< endl;
	a.show();
	a.Delete(a.FirstNode()->next, a.LastNode()->prev);
	a.show();
	a.Delete(a.FirstNode());
	a.show();
	a.Delete(a.LastNode());
	for (int i=0; i<10; i++)
		a.PushFront(i);
	a.show();
	a.Insert(a.FirstNode()->next, 10);
	a.show();
	b=a;
	a.show();
	b.show();
	TNode* tp=a.Extract(a.FirstNode());
	a.show();
	b=a.Extract(a.FirstNode()->next, a.LastNode()->prev);
	b.show();
	for (int i=0; i<10; i++)
		b.PushBack(i);
	a.show();
	b.show();
	TNode* tp1;
	a.Insert(a.FirstNode(), b);
	a.show();
    }

    cout << "Created: " << Created << endl;
    cout << "Deleted: " << Deleted << endl;
    return 0;
}

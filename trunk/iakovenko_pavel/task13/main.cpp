#include <iostream>
using namespace std;

struct TNode{
	int value;
	TNode *next, *prev;
	TNode(){
		prev=0;
		next=0;
		value=0;
	};
	explicit TNode(int a){
		value=a;
		prev=0;
		next=0;
	};
	TNode(int a, TNode *p, TNode *n){
		value=a;
		prev=p;
		next=n;
	};
	~TNode(){
		printf("TNode, val=%d\n",value);
	};

};

class TList{
public: //should be private, but I made it for the tests
	TNode* first;
	TNode* last;
public:
TList(){
	first=0;
	last=0;
};

TList(const TList& other){
	if (other.first==0){
			TList();
			return;
		}
		TNode *p=new TNode(other.first->value);
		first=p;
		TNode *curp=other.first;
		for(;curp;curp->next, p=p->next){
			TNode *np=new TNode(curp->value, p, 0);
			p->next=np;			
		}
		last=p;
};

TList& operator=(const TList &other){
	first=0;
	last=0;
	TNode* temp=other.first;
	while (temp->next!=0){
		PushBack(temp);
		temp=temp->next;
	}
	PushBack(temp);
};

~TList(){
	for(;first;first=first->next){
			TNode *p=first->next;
			delete first;
			first=p;
		}
};

bool IsEmpty() const{
	return (first==0)? true: false;
};

int First() const{
	return first->value;;
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
	if (first==0)
	{first=last=node;
	node->prev=0;
	}
	else{
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
	node->prev=0;
	}
	else{
		node->prev=last;
		last->next=node;
		last=node;
	}
};

void Insert(TNode* where, int val){
	TNode* n=new TNode;
	n->value=val;
	Insert(where,n);
};

void Insert(TNode* where, TNode* node){
	(where->prev)->next=node;
	node->prev=where->prev;
	node->next=where;
	where->prev=node;
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

TNode* ExtractLast(){
	return Extract(last);
};	

TNode* ExtractFirst(){
	return Extract(first);
};

void Delete(TNode* node){
	if(first!=last){
		if(node->prev!=0)
			(node->prev)->next=node->next;
		else{
			node->next->prev=0;
			first=node->next;
		}
		if(node->next!=0)
			(node->next)->prev=node->prev;
		else{
			node->prev->next=0;
			last=node->prev;
		}
		delete node;
	}
	else{
		delete node;
		first=0;
		last=0;
	}
};

void Delete(TNode* from, TNode *to){
	    (from->prev)->next=to->next;
		(to->next)->prev=from->prev;
		TNode* temp=from;
		while(temp->next!=to->next){
			TNode* t=temp->next;
			Delete(temp);
			temp=t;
		}
		Delete(to);
};

TNode* Extract(TNode* node){
	if(node==first)
		first=node->next;
	else
		node->prev->next=node->next;
	if(node==last)
		last=node->next;
	else
		node->next->prev=node->prev;
	return node;
};

TList Extract(TNode* from, TNode* to){
	TList temp;
	temp.first=from;
	temp.first->prev=0;
	temp.last=to;
	temp.last->next=0;
	if(from->prev!=0)
		(from->prev)->next=to->next;
	else 
		first=to->next;
	if(to->next!=0)
		(to->next)->prev=from->prev;
	else
		last=to->prev;
	return temp;
};
};

int main(){
	return 0;
}
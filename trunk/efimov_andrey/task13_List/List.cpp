#include <iostream>

using namespace std;

struct TNode{
// default - public:
	int val;
	TNode *prev, *next;
	TNode(){
		prev=0;
		next=0;
		val=0;
	}
	TNode(int a){
		prev=0;
		next=0;
		val=a;
	}
	TNode(int a, TNode* p, TNode* n){
		val=a;
		prev=p;
		next=n;
	}
	~TNode(){
		cout << "~TNode, val = " << val;
	}
};

class TList{
// default - private:
	TNode *first;
	TNode *last;
public:
	TList(){
		first=0;
		last=0;
	}
	TList(TNode* l, TNode* r){
		first=l;
		last=r;
	}
	TList(const TList &a){
		if (a.first !=0){
			TNode*p=new TNode(a.first->val);
			first=p;
			TNode* c=a.first->next;
			for(;c;c=c->next, p=p->next){
				TNode *np=new TNode (c->val, p, 0);
				p->next=np;
			}
			last=p;
		}
		else{
			TList();
			return;
		}
	}
	int First() const{
		return first->val;
	}
	int Last() const{
		return last->val;
	}
	TList& operator=(const TList &other);

	bool IsEmpty() const{
		return (first==0) ? 1 : 0;
	}
	void Insert(TNode* pos, int v){
		TNode* p = new TNode(v);
		Insert (pos, p);
	}
	void Insert(TNode* pos, TNode* p){
		if (first==0){
			first=p;
			last= p;
			return;
		}
		if (first==pos){
			first = p;
		}
		else{
			p->prev = pos->prev;
			p->prev->next = p;
		}
		p->next = pos;
		pos->prev = p;
	}
	void Insert(TNode* pos, TList &that){
		if (pos!=first) pos->prev->next=that.first;
		else first=that.first;
		that.first->prev=pos->prev;
		pos->prev=that.last;
		that.last->next=pos;
		that.first=0;
		that.last=0;
	}
	void Pushfront(int v){
		Insert (first, v);
	}
	void Pushfront(TNode* p){
		Insert (first, p);
	}
	void Pushback (int v){
		TNode *p = new TNode(v);
		Pushback (p);
	}
	void Pushback (TNode* p){
		p->prev = last;
		if (last!=0){
			last->next = p;
		}
		else{
			first=p;
		}
		last=p;
	}
	void Delete (TNode* n){
		if (n->prev!=0) n->prev->next=n->next;
		if (n->next!=0) n->next->prev=n->prev;
		if (n==first) first=n->next;
		if (n==last) last=n->prev;
	}
	void Delete (TNode* l, TNode* r){
		TNode* c=l;
		for (c;c!=r;c=c->next){
			Delete(c);
		}
		Delete(r);
	}
	int PopFirst(){
		TNode* c=first;
		int v=c->val;
		first=c->next;
		delete c;
	}
	int PopLast(){
		TNode* c=last;
		int v=c->val;
		last=c->prev;
		delete c;
	}
	TNode* Extract(TNode *n){
		if (n==first) first=n->next;
		else n->prev->next=n->next;
		if (n==last) last=n->prev;
		else n->next->prev=n->prev;
		return n;
	}
	TNode* ExtractFirst(){
		Extract(first);
	}
	TNode* ExtractLast(){
		Extract(last);
	}
	TList Extract(TNode* l, TNode* r){
		TList F (l, r);
		if (l==first) first=r->next;
		else l->prev->next=r->next;
		if (r==last) last=l->prev;
		else r->next->prev=l->prev;
		l->prev=0;
		r->next=0;
		return F;
	}
	const TNode* FirstNode() const{
		return first;
	}
	const TNode* LastNode() const{
		return last;
	}
	void Print(){
		for (TNode *a=first; a!=0; a=a->next)
			cout << a->val;
	}
	~TList(){
		TNode* p;
		for (;first;first=p){
			p=first->next;
			delete first;
		}
	}
};

int main(){
	TList p;
	return 0;
}
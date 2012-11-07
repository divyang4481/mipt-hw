#include<iostream>
using namespace std;
struct list
{   
	int x;
	list *prev,*next;
};
class TList
{   
   
    public:
    //private;
	list *first,*last;
    public:
	TList()
	{
		first=NULL;
		last=NULL;
	};
	TList(const TList& other)
	{
		first=NULL;
		last=NULL;
		list *dop;
		dop=other.first;
		while(dop!=other.last)
		{
			PushBack(dop->x);
			dop=dop->next;
		}
		PushBack(dop->x);
	};
	void operator=(const TList& other)
	{ 
		first=NULL;
		last=NULL;
		list *dop;
		dop=other.first;
		while(dop!=other.last)
		{
			PushBack(dop->x);
			dop=dop->next;
		}
		PushBack(dop->x);
	};
	~TList()
	{
		while(first)
		{
			last=first->next;
			delete first;
			first=last;
		}
	};
	bool IsEmpty() const
	{
		return(first==NULL);
	};
	int First() const
	{	
	    return(first->x);
	};
	int Last() const
	{	
	    return(last->x);
	};
	const list* FirstNode() const
	{
		return first;
	};
	const list* LastNode() const
	{
		return last;
	};
	void PushBack(int val)
	{
		list *n=new list;
		n->x=val;
		n->next=NULL;
		if(first!=NULL)
		{
			n->prev=last;
			last->next=n;
			last=n;
		}
		else
		{
			n->prev=NULL;
			first=last=n;
		}
	};
	void PushBack(list* node)
	{
		node->next=NULL;
		if(first!=NULL)
		{
			node->prev=last;
			last->next=node;
			last=node;
			node=NULL;
		}
		else 
		{
			node->prev=NULL;
			first=last=node;
			node=NULL;
		}
	};
	void PushFront(int val)
	{
	    list *n=new list;
		n->x=val;
		n->prev=NULL;
		if(first!=NULL)
		{
			n->next=first;
			first->prev=n;
			first=n;
		}
		else
		{
			n->next=NULL;
			first=last=n;
		}
	};
	void PushFront(list* node)
	{
		node->prev=NULL;
		if(first!=NULL)
		{
			node->next=first;
			first->prev=node;
			first=node;
		}
		else 
		{
			node->next=NULL;
			first=last=node;
		}
	};
	void Insert(list* where, int val)
	{   
		list* n=new list;
		n->x=val;
		if(where->prev!=NULL)
		{
			where->prev->next=n;
			n->prev=where->prev;
			n->next=where;
			where->prev=n;
		}
		else PushBack(n);
	};
	void Insert(list* where,list* node)
	{
		if(where->prev!=NULL)
		{
			where->prev->next=node;
			node->prev=where->prev;
			node->next=where;
			where->prev=node;
			node=NULL;
		}
		else PushBack(node);
	};
	void Insert(list* where,TList& other)
	{
		if(where->prev!=NULL)
		{
			where->prev->next=other.first;
			other.first->prev=where->prev;
			other.last->next=where;
			where->prev=other.last;
			other.first=NULL;
			other.last=NULL;
		}
		else 
		{
			other.first->prev=NULL;
			other.last->next=where;
			where->prev=other.last;
			first=other.first;
			other.first=NULL;
			other.last=NULL;	
		}
	};
	int PopLast()
	{
		int k=last->x;
		last=last->prev;
		delete last->next;
		last->next=NULL;
		return k;
	};
	int PopFirst()
	{
		int k=first->x;
		first=first->next;
		delete first->prev;
		first->prev=NULL;
		return k;
	};
	void show()
	{
		list *k=first;
		if (first!=NULL)
		{
		while(k!=last)
		{cout<<k->x<<' ';k=k->next;}
		cout<<k->x<<'\n';
		}
	}
	list* ExtractLast()
	{
		list *k=last;
		if(first!=last)
		{
		last=last->prev;
		last->next=NULL;
		k->prev=NULL;
		}
		else first=last=NULL;
		return k;
	};
	list* ExtractFirst()
	{
		list *k=first;
		if(first!=last)
		{
			first=first->next;
		    first->prev=NULL;
		    k->next=NULL;
		}
		else first=last=NULL;
		return k;
	};
	void Delete(list* node)
	{
		if(node->prev!=NULL)node->prev->next=node->next;
		if(node->next!=NULL)node->next->prev=node->prev;
		delete node;
	};
	void Delete(list* from, list *to)
	{
		while(from!=to)
		{
			from=from->next;
			Delete(from->prev);
		}
		Delete(from);
	};
	list* Extract(list* node)
	{
		list *k=node;
		if(node->prev!=NULL)node->prev->next=node->next;else first=node->next;
		if(node->next!=NULL)node->next->prev=node->prev;else last=node->prev;
		node=NULL;
		return k;
	};
	TList Extract(list* from, list* to)
	{
		TList k;
		if(from->prev!=NULL)from->prev->next=to->next;else first=to->next;
		if(to->next!=NULL)to->next->prev=from->prev;else last=from->prev;
		while(from!=to)
		{
			k.PushBack(from->x);
			from=from->next;
			delete from->prev;
		}
		k.PushBack(from);
		from=to=NULL;
		return k;
	};
};
int main()
{
	TList a,b,c;
	for(int i=0;i<10;++i)a.PushBack(i);
	a.show();
	b=a.Extract(a.first->next->next,a.last->prev);
	a.show();
	b.show();
	list *k;
	k=b.Extract(b.first);
	b.show();
	a.PushFront(k);
	a.show();
	b.Delete(b.first->next,b.last->prev);
	b.show();
	while(a.first)
	{
	k=a.ExtractFirst();
	b.PushBack(k);
	}
	a.show();
	b.show();
	int kk;
	kk=b.PopFirst();
	cout<<kk<<'\n';
	b.show();
	c=b;
	for(int i=0;i<kk;++i)a.PushFront(kk);
	a.show();
	k=b.last;
	b.Insert(k,c);
	b.show();
	b.Insert(k,a.ExtractFirst());
	b.Insert(k,100);
	b.show();
	a.show();
	c.show();
	return 0;
}
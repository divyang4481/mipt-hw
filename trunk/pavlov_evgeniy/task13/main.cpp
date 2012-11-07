#include<iostream>
using namespace std;
struct list
{   
	int x;
	list *prev,*next;
};
class TList
{   
    private:
    public:
	list *first,*last;
	public:
	TList()
	{
		first=NULL;
		last=NULL;
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
		list *k;
		k=first;
		while(k!=last)
		{cout<<k->x<<' ';k=k->next;}
		cout<<k->x<<'\n';
	}
	list* ExtractLast()
	{
		list *k=last;
		last=last->prev;
		last->next=NULL;
		k->prev=NULL;
		return k;
	};
	list* ExtractFirst()
	{
		list *k=first;
		first=first->next;
		first->prev=NULL;
		k->next=NULL;
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
			delete from->prev;
		}
		delete from;
	};
	list* Extract(list* node)
	{
		list *k=node;
		if(node->prev!=NULL)node->prev->next=node->next;
		if(node->next!=NULL)node->next->prev=node->prev;
		node=NULL;
		return k;
	};
	TList Extract(list* from, list* to)
	{
		TList k;
		if(from->prev!=NULL)from->prev->next=to->next;
		if(to->next!=NULL)to->next->prev=from->prev;
		while(from!=to)
		{
			k.PushBack(from);
			from=from->next;
		}
		k.PushBack(from);
		from=to=NULL;
		return k;
	};
};

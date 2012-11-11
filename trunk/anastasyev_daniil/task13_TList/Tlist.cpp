#include <iostream>
using namespace std;

class TNode
 {
 public:
    int val;
    TNode *prev, *next;
    TNode()
    {
        val = 0;
        prev = 0;
        next = 0;
    }
    TNode(int a)
    {
        val = a;
        prev = 0;
        next = 0;
    }
    TNode(int a, TNode *p, TNode *n)
    {
        val = a;
        prev = p;
        next = n;
    }
};

class TList
{
private:
    

public:
    TNode *first, *last;
    TList()
    {
        first = 0;
        last = 0;
    }
    TList(const TList& other)
    {
        if (other.first == 0)
        {
            TList();
            return;
        }
        TNode *p = new TNode(other.first->val);
        first = p;
        TNode *curp = other.first->next;
        for (; curp; curp=curp->next, p=(*p).next) 
        {
            TNode *np = new TNode((*curp).val,p,0);
            (*p).next = np;
        }
        last = p;
    }

    TList (TNode* f, TNode* l)
    {
        TNode *p = new TNode(f->val);
        first = p;
        TNode *curp = f->next;
        for (; curp!=l->next; curp=curp->next, p=(*p).next) 
        {
            TNode *np = new TNode((*curp).val,p,0);
            (*p).next = np;
        }
        last = p;
	}

    ~TList()
    {
        for( ; first; ) 
        {
            TNode *p = (*first).next;
            delete first;
            first=p;
        }
    }
    bool IsEmpty() const
    {
        if (first) return false;
        else return true;
    }

    const TNode *FirstNode() const
    {
        return first;
    }
    
    TNode *FirstNode()
    {
        return first;
    }
    
    const TNode *LastNode() const
    {
        return last;
    }
    
    TNode *LastNode()
    {
        return last;
    }

    void PushBack(TNode* node)
    {
        node->prev = last;
        if (last != 0) last->next=node;
        else first=node;
        last=node;
    }

    void PushBack(int val)
    {
        TNode *p = new TNode(val);
        PushBack(p);
    }

    void PushFront(TNode* node)
    {
        node->next = first;
        if (first != 0) first->prev=node;
        else last=node;
        first=node;
    }

    void PushFront(int val)
    {        
        TNode *p = new TNode(val);
        PushFront(p);
    }

    void Insert(TNode* where, TNode* node)
    {
        if (!first) 
        {
            first = node;
            last = node;
            return;
        }
        node->next = where;
        if (where==first)
        {
            first=node;
        }
        else 
        {
           node->prev = where->prev;
           node->prev->next = node;
       }
    }

    void Insert(TNode* where, int val)
    {
        TNode *p = new TNode (val);
        Insert(where, p);
    }

    void Insert(TNode* where, TList &other)
    {
        if (where!=first)
        {
            where->prev->next = other.first;
		    other.first->prev = where->prev;
            where->prev = other.last;
            other.last->next = where;
        }
        else
        { 
            first = other.first;
            where->prev = other.last;
            other.last->next = where;
        }
        other.first=0;
        other.last=0;
    }

    void Delete(TNode* node)
    {
    	if (node->prev!=0) node->prev->next = node->next;
		if (node->next!=0) node->next->prev = node->prev;
		if (node==first) first = node->next;
		if (node==last) last = node->prev;
    }

    void Delete(TNode* from, TNode *to)
    {
    	if ((from->prev!=0) && (to->next!=0))
            {
                from->prev->next = to->next;
		        to->next->prev = from->prev;
            }
		if (from==first) first = to->next;
		if (to==last) last = from->prev;
    }

    int PopLast()
    {
		int val = last->val;
		last = last->prev;
		delete last;
        return val;
    }

    int PopFirst()
    {
		int val = first->val;
		first = first->next;
		delete first;
        return val;
    }

    TNode* Extract(TNode* node)
    {
        if (node==first) first = node->next;
		else node->prev->next = node->next;
		if (node==last) last = node->prev;
		else node->next->prev = node->prev;
		return node;
    }

    TNode* ExtractFirst()
    {
        Extract(first);
    }

    TNode* ExtractLast()
    {
        Extract(last);
    }

    TList Extract(TNode* from, TNode* to)
    {
        TList N(from, to);
        Delete(from,to);
		return N;
    }

    void Print()
    {
        for (TNode *a=first; a; a=(*a).next) printf("%d ",(*a).val);
        printf("\n");
    }
};

int main()
{
    TList p;
    return 0;
}
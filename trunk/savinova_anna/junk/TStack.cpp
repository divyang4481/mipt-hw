#include "cstdio"
#include "string.h"

struct TNode
{
    int val;
    TNode *next;
    explicit TNode()
    {
        next = 0;
        val = 0;
    }
    explicit TNode(int a)
    {
        next = 0;
        val = a;
    }
    explicit TNode(int a, TNode* p, TNode* n)
    {
        val = a;
        next = n;
    }
    ~TNode()
    {
        printf("~TNode, val=%d\n",val);
    }
};

class TStack
{
public:
    TNode *first;
    TStack()
    {
        first = 0;
    }
    ~TStack()
    {
        for (;first;)
        {
            TNode *p = first -> next;
            delete first;            
            first = p;
        }
    }
    bool IsEmpty() const
    {
        if (first) return false;
        return true;
    };
    int First() const
    {
        return first -> val;
    }
    void Push(int val)
    {
        TNode *p = new TNode(val);
        p -> next = first;
        first = p;
    };
    int Pop()
    {
        TNode* tmp1 = first -> next;
        int tmp2 = first -> val;        
        delete first;
        first = tmp1;
        return tmp2;
    };
    void Print()
    {
        if (first == 0)
        {
            printf("Empty");
            return;
        };
        for (TNode *a = first; a != 0; a = a -> next)
            printf("%d ", a -> val);
    };
};
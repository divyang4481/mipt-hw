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
    void Push(int val)
    {
        TNode *p = new TNode(val);
        p -> next = first;
        first = p;
    };
    void Delete()
    {
        TNode* tmp = first -> next;   
        delete first;
        first = tmp;
        return;
    };
};

int main()
{
    char C = 0;
    bool Cor = true;
    TStack S;
    scanf("%c", &C);
    while (C != 10)
    {
        if (C == '(')
            S.Push(0);
        else
        {
            if (S.IsEmpty())
                Cor = false;
            else S.Delete();
        }
        scanf("%c", &C);
    }
    if (Cor && S.IsEmpty())
        printf("YES");
    else printf("NO");
    return 0;
}
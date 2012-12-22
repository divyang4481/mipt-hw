#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int Created = 0;
int Deleted = 0;

struct TNode
{
    int val;
    TNode *prev;
    TNode *next;
    TNode()
    {
        ++Created;
        prev = 0;
        next = 0;
        val = 0;
    }
    TNode(int a)
    {
        ++Created;
        prev = 0;
        next = 0;
        val = a;
    }
    ~TNode() {
        ++Deleted;
    }
};

class TList
{
    TNode *first;
    TNode *last;
public:
    TList()
    {
        first = 0;
        last = 0;
    }
    ~TList()
    {
        Delete(FirstNode(), LastNode());
    }
    TList(const TList &other)
    {
        *this = other;
    }
    TList& operator=(const TList &other)
	{
	    first = 0;
        last = 0;
        if(this!=&other)
        {
            TNode *a;
            a = other.first;
            while(a != other.last)
            {
                PushBack(a->val);
                a = a->next;
            }
            PushBack(a->val);
        }
        return *this;
	};
    bool IsEmpty()
    {
        return (first == last);
    }
    int First() const
    {
        if (first != 0)
            return first->val;
        else
            return -1;
    }
    int Last() const
    {
        if (last != 0)
            return last->val;
        else
            return -1;
    }
    TNode* FirstNode() const
    {
        return first;
    }
    TNode* LastNode() const
    {
        return last;
    }
    void PushBack(int val) // вставляет в конец списка элемент со значением val
    {
        TNode *p = new TNode(val);
        PushBack(p);
    }
    void PushBack(TNode* node) // вставляет в конец списка узел node.
    {
        node->prev = last;
        if (first != 0)
        {
            last->next = node;
        }
        else
        {
            first = node;
        }
        last = node;
    }
    void PushFront(int val) // вставляет в начало спика элемент со значением val
    {
        TNode *p = new TNode(val);
        PushFront(p);
    }
    void PushFront(TNode* node) // вставляет в начало списка узел node.
    {
        node->next = first;

        if (last != 0)
        {
            first->prev = node;
        }
        else
        {
            last = node;
        }
        first = node;
    }
    void Insert(TNode* where, int val) // вставляет перед узлом where узел со значением val
    {
        TNode *p = new TNode(val);
        Insert(where, p);
    }
    void Insert(TNode* where, TNode* node) // вставляет перед узлом where узел node.
    {
        if (where->prev == 0)
        {
            PushFront(node);
        }
        else
        {
            node->prev = (where->prev)->next;
            (where->prev)->next = node;
            node->next = where;
            where->prev = node;
        }
    }
    void Insert(TNode* where, TList &other) // вставляет перед узлом where все элементы списка other (за O(1)).
    {
    if (where->prev == 0)
        {
            first = other.first;

        }
        else
        {
            (where->prev)->next = other.first;
            (other.first)->prev = where->prev;
        }

        (other.last)->next = where;
        where->prev = other.last;

        other.first = 0;
        other.last = 0;
    };

    int PopLast()  // извлекает из списка последний элемента, освобождает память и возвращает значение элемента
    {

        int a = last->val;
        if (first == last)
        {
            delete first;
            first = 0;
            last = 0;
        }
        else
        {
            last = last->prev;
            delete last->next;
            last->next = 0;
        }
        return a;
    };
    int PopFirst() // извлекает из списка первый элемент, освобождает память и возвращает значение элемента
    {
        int a = first->val;
        if (first == last)
        {
            delete first;
            first = 0;
            last = 0;
        }
        else
        {
            first = first->next;
            delete first->prev;
            first->prev = 0;
        }
        return a;
    };

    TNode* ExtractLast() // извлекает из списка последний узел и возвращает указатель на него;
    {
        TNode *a = new TNode;
        a = last;
        return Extract(a);
    };
    TNode* ExtractFirst() // извлекает из списка первый узел и возвращает указатель на него;
    {
        TNode *a = new TNode;
        a = last;
        return Extract(a);
    };

    void Delete(TNode* node) // удаляет из списка узел node
    {
        if (node->next != 0)
        {
            (node->next)->prev = node->prev;
        }
        else
        {
            last=node->prev;
        }
        if (node != first)
        {
            (node->prev)->next = node->next;
        }
        else
        {
            first=node->next;
        }
        delete node;
    };
    /*void Delete(TNode* from, TNode *to) // удаляет из списка все элемента от from до to
    {
        if (from->prev == 0)
        {
            Delete(from);
        }
        else
        {
            TNode *cur = from->next;
            while (cur != to->next)
            {
                Delete(cur->prev);
                cur = cur->next;
            }
            Delete(to);
            delete cur;
        }
    };*/
    void Delete(TNode *from, TNode *to)
	{
		if (from->prev != 0)
		{
		    (from->prev)->next = to->next;
		}
        else
        {
            first = to->next;
        }
		if (to->next != 0)
		{
		    (to->next)->prev = from->prev;
        }
        else
        {
            last=from->prev;
        }
		TNode *k;
		k = (from->next)->prev;
		while (k != to->prev)
		{
			k = k->next;
			delete k->prev;
		}
		delete k;
		delete to;
	};
    TNode* Extract(TNode* node) // извлекает из списка узел node и возвращает указатель на него;
    {
        if ((node == last) && (node == first))
        {
            first = 0;
            last = 0;
        }
        if (node != last)
        {
            (node->next)->prev = node->prev;
        }
        if (node != first)
        {
            (node->prev)->next = node->next;
        }
        return node;
    };
    TList Extract(TNode* from, TNode* to) // извлекает из списка интервал элментов от from до to.
    {
        TList a;
        a.first = from;
        a.last = to;
        if ((to == last) && (from == first))
        {
            first = 0;
            last = 0;
        }
        if (to != last)
        {
            (to->next)->prev = from->prev;
        }
        if (from != first)
        {
            (from->prev)->next = to->next;
        }
        from->prev = 0;
        to->next = 0;
        return a;
    };
    void Print()
    {
        for (TNode *i = first; i != 0; i = i->next)
            printf("%d ", i->val);
        cout << endl;
    };
};

int main()
{
    {
        /*
        TList List;
        cout << "10-element list with values from 1 to 10" << endl;
        for (int i = 1; i <= 10; ++i)
        {
            List.PushBack(i);
        }
        List.Print();
        cout << "Insert 100 in the front" << endl;
        List.PushFront(100);
        List.Print();

        cout << "Split into 2 separate lists" << endl;
        TNode* i = (List.FirstNode()) -> next;
        TNode* j = (List.LastNode()) -> prev;
        TList List1 = List.Extract(i,j);
        List1.Print();
        List.Print();

        cout << "Make a second list with the 2 first and 2 last elements from the first one" << endl;
        TList List2 = List1;
        i = (List2.FirstNode()) -> next -> next;
        j = (List2.LastNode()) -> prev -> prev;
        List2.Delete(i,j);
        List2.Print();
        cout << "Delete those elements from the first list" << endl;
        List1.Delete(List1.FirstNode());
        List1.Delete(List1.FirstNode());
        List1.Delete(List1.LastNode());
        List1.Delete(List1.LastNode());
        List1.Print();
        List.Print();
        */

        TList l1;
        for (int i = 0; i < 10; ++i)
            l1.PushBack(i);

        TList l2(l1);

        TList l3;
        for (int i = 0; i < 5; ++i)
            l3.PushBack(i);

        l3 = l2;
        l2 = l1;
    }

    cout << "Created: " << Created << endl;
    cout << "Deleted: " << Deleted << endl;
    return 0;
}

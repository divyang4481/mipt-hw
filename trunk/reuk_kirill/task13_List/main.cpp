#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct TNode
{
    int val;
    TNode *prev;
    TNode *next;
    TNode()
    {
        prev = 0;
        next = 0;
        val = 0;
    }
    TNode(int a)
    {
        prev = 0;
        next = 0;
        val = a;
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
    TList(const TList &other)
    {
        first = other.first;
        last = other.last;
    }
   /* Tlist& operator=(const TList &other){
        TNode *current = first;
        TNode *othercurrent = other.first;
        while (current <> 0)
        {
            othercurrent.val = current.val;
            current = current.next;
            if othercurrent.next
        }*/
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

    const TNode* FirstNode() const
    {
        return first;
    }
    const TNode* LastNode() const
    {
        return last;
    }
    void PushBack(int val) // ��������� � ����� ������ ������� �� ��������� val
    {
        TNode *p = new TNode(val);
        PushBack(p);
    }
    void PushBack(TNode* node) // ��������� � ����� ������ ���� node.
    {
        node->prev = last;
        last = node;
        if (first != 0)
        {
            last->next = node;
        }
        else
        {
            first = node;
        }
    }
    void PushFront(int val) // ��������� � ������ ����� ������� �� ��������� val
    {
        TNode *p = new TNode(val);
        PushFront(p);
    }
    void PushFront(TNode* node) // ��������� � ������ ������ ���� node.
    {
        node->next = first;
        first = node;
        if (last != 0)
        {
            first->prev = node;
        }
        else
        {
            last = node;
        }
    }
    void Insert(TNode* where, int val) // ��������� ����� ����� where ���� �� ��������� val
    {
        TNode *p = new TNode(val);
        Insert(where, p);
    }
    void Insert(TNode* where, TNode* node) // ��������� ����� ����� where ���� node.
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
    void Insert(TNode* where, TList &other) // ��������� ����� ����� where ��� �������� ������ other (�� O(1)).
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

    int PopLast()  // ��������� �� ������ ��������� ��������, ����������� ������ � ���������� �������� ��������
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
    int PopFirst() // ��������� �� ������ ������ �������, ����������� ������ � ���������� �������� ��������
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

    TNode* ExtractLast() // ��������� �� ������ ��������� ���� � ���������� ��������� �� ����;
    {
        TNode *a = new TNode;
        a = last;
        return Extract(a);
    };
    TNode* ExtractFirst() // ��������� �� ������ ������ ���� � ���������� ��������� �� ����;
    {
        TNode *a = new TNode;
        a = last;
        return Extract(a);
    };

    void Delete(TNode* node) // ������� �� ������ ���� node
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
        delete node;
    };
    void Delete(TNode* from, TNode *to) // ������� �� ������ ��� �������� �� from �� to
    {
        TNode *cur = new TNode();
        cur = from->next;
        do
        {
            delete(cur->prev);
        }
        while (cur->next != to);
    delete(to);
    delete cur;
    };

    TNode* Extract(TNode* node) // ��������� �� ������ ���� node � ���������� ��������� �� ����;
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

    TList Extract(TNode* from, TNode* to) // ��������� �� ������ �������� �������� �� from �� to.
    {
        TList a;
        a.first = from;
        a.last = to;
        if ((from == last) && (from == first))
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
        return a;
    };
};

int main()
{
    TList a;

    return 0;
}

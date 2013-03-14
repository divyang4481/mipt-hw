#include <iostream>
using namespace std;

template <typename T>
struct TNode {
    T val;
    TNode<T> *prev, *next;
    explicit TNode() {
        prev = 0;
        next = 0;
        val = 0;
    }
    ~TNode(){
    }
};

template <typename T>
class TList {
    TNode<T> *first;
    TNode<T> *last;
public:
    TList<T> () {
        first = 0;
        last = 0;
    }
    TList<T> (const TList &lst)
    {
        if (lst.first == 0)
        {
            TList();
            return;
        }
        TNode *p = new TNode(lst.first -> val);
        first = p; 
        TNode *curp = lst.first -> next;
        for (; curp; curp = curp -> next, p = p -> next)
        {
            TNode* np = new TNode(curp -> val, p, 0);
            p -> next = np;
        }
        last = p;
    }
    ~TList()
    {
        for (;first;)
        {
            TNode *p=first -> next;
            delete first;            
            first=p;
        }
    }
    bool Empty() const//пустой ли
    {
        if (first) return false;
        return true;
    };
    int First() const
    {
        return first -> val;
    };
    int Last() const
    {
        return last -> val;
    };
    const TNode* FirstNode() const
    {
        return first;
    };
    const TNode* LastNode() const
    {
        return last;
    };
    void PushBack(int val)
    {
        TNode *p = new TNode(val);
        p -> prev = last;
        if (last != 0)
            last -> next = p;
        else first = p;
        last = p;
    };
    void PushBack(TNode* node)
    {
        node -> prev = last;
        if (last != 0)
            last -> next = node;
        else first = node;
        last = node;
    };    
    void PushFront(int val)
    {
        TNode *p = new TNode(val);
        p -> next = first;
        if (first != 0)
            first -> prev = p;
        else last = p;
        first = p;
    };
    void PushFront(TNode* node)
    {
        node -> next = first;
        if (first != 0)
            first -> prev = node;
        else last = node;
        first = node;
    };
    void Insert(TNode* where, int val) //указатель на то, что он заменит(следующий)
    {
        TNode *p = new TNode(val);
        if (first == 0)
        {
            first=p;
            last=p;
            return;
        }
        if (first == where)
        {
            p -> next = first;
            first=p;
        }
        else
        {
            p -> prev = where -> prev;            
            p -> prev -> next = p;
            where -> prev = p;
            p -> next = where;
        }
    };
    void Insert(TNode* where, TNode* node)
    {
        if (first == 0)
        {
            first=node;
            last=node;
            return;
        }
        if (first == where)
        {
            node -> next = first;
            first = node;
        }
        else
        {
            node -> prev = where -> prev;            
            node -> prev -> next = node;
            where -> prev = node;
            node -> next = where;
        }
    };
    void Insert(TNode* where, TList &other)
    {
        if (first == where)
        {
            other.last -> next = where;
            first -> prev = other.last;
            first = other.first;
        }
        else
        {
            other.first -> prev = where -> prev;
            where -> prev -> next = other.first;
            other.last -> next = where;
            where -> prev = other.last;
        }        
        other.first=0;
        other.last=0;
    };
    int PopLast()
    {
        int val = last -> val;
        TNode* tmp = last;
        last = last -> prev;
        last -> next = 0;
        delete tmp;
        return val;
    };
    int PopFirst()
    {
        int val = first -> val;
        TNode* tmp = first;
        first = first -> next;
        first -> prev = 0;
        delete tmp;
        return val;
    };
    TNode* ExtractLast()
    {
        TNode* tmp = last;
        last = last -> prev;
        last -> next = 0;
        return tmp;
    }; // извлекает из списка последний узел и возвращает указатель на него, за владение узла отвечает вызвавший метод клиентский код
    TNode* ExtractFirst()
    {
        TNode* tmp = first;
        first = first -> next;
        first -> prev = 0;
        return tmp;
    };// извлекает из списка первый узел и возвращает указатель на него, за владение узла отвечает вызвавший метод клиентский код
    void Delete(TNode* node)
    {
		TNode* tmp = node;
        node -> prev -> next = node -> next;
        node -> next -> prev = node -> prev;
		delete tmp;
    };
    void Delete(TNode* from, TNode *to)
    {
        TNode* tmp = from -> next;
        while (tmp != to)
        {
            tmp = tmp -> next;
            delete tmp -> prev;
        }
        from -> next = to;
        to -> prev = from;
    };
    TNode* Extract(TNode* node)
    {
        TNode* tmp = node;
        node -> prev -> next = tmp -> next;
        node -> next -> prev = tmp -> prev;
        delete node;
        return tmp;
    };    
    TList Extract(TNode* from, TNode* to)
    {
        TList tmp;
        from = from -> prev;
        while (from != to)
        {
            from = from -> next;
            TNode* t = Extract(from);
            tmp.PushBack(t);            
        }
        return tmp;
    }; // извлекает из списка интервал элментов от from до to. возвращает объект TList, содержащий этот интервал
    void Print()
    {
        for (TNode *a = first; a != 0; a = a -> next)
            printf("%d ", a -> val);
    };
};

int main()
{
    //TNode n = 1; //вызов конструктора TNode n(1) Если нет explicit;
    TList p;
    /*for (int i=1; i<6; ++i)
        p.PushBack(i);    
    p.Insert(p.LastNode(),7);
    p.Print();
    TList lst(p);
    lst.Print();*/
	return 0;
}
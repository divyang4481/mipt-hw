#include <iostream>

using namespace std;

struct TNode
{
    int key;
    TNode* prev;
    TNode* next;
};
class TList
{
  private:
    int size;
    TNode* first;
    TNode* last;
  public:
    TList()
    {
        first = last = NULL;
        size = 0;
    }
    TList(const TList& other)
    {
        first = last = NULL;
        size = 0;
        const TNode* toother = other.FirstNode();
        for (;toother != NULL; toother = toother -> next)
          PushBack(toother -> key);

    }
    TList& operator=(const TList &other)
    {
        Delete(first, last);
        //TList(other);
        const TNode* toother = other.FirstNode();
        for (;toother != NULL; toother = toother -> next)
          PushBack(toother -> key);
        return *this;

    }
    ~TList()
    {
        Delete(first, last);
    }

    const TNode* FirstNode() const
    {
        return first;
    }
    const TNode* LastNode() const
    {
        return last;
    }
    TNode* FirstNode()
    {
        return first;
    }
    TNode* LastNode()
    {
        return last;
    }
    bool IsEmpty() const
    {
        return(first == NULL);
    }
    int First()
    {
        return first -> key;
    }
    int Last()
    {
        return last -> key;
    }
    void PushBack(int key)
    {
        TNode* node = new TNode;
        node -> key = key;
        PushBack(node);
        /*node -> next = NULL;
        if (first == NULL)
        {
            node -> prev = NULL;
            first = last = node;
        }
        else
        {
            node -> prev = last;
            last -> next = node;
            last = node;
        }
        ++size;*/
    }
    void PushBack(TNode* node)
    {

        node -> next = NULL;
        if (first == NULL)
        {
            node -> prev = NULL;
            first = last = node;
        }
        else {
            node -> prev = last;
            last -> next = node;
            last = node;
        }
        ++size;
    }
    void PushFront(int key)
    {
        TNode* node = new TNode;
        node -> key = key;
        PushFront(node);
        /*node -> prev = NULL;
        if (first == NULL)
        {
            node -> next = NULL;
            first = last = node;
        }
        {
            first -> prev = node;
            node -> next = first;
            first = node;
        }
        ++size;*/
    }
    void PushFront(TNode* node)
    {
        node -> prev = NULL;
        if (first == NULL)
        {
            node -> next = NULL;
            first = last = node;
        }
        {
            first -> prev = node;
            node -> next = first;
            first = node;
        }
        ++size;
    }
    void Insert(TNode* where, int key)
    {
        TNode* node = new TNode();
        node -> key = key;
        Insert(where, node);
    }
    void Insert(TNode* where, TNode* node)
    {
        TNode* help = where -> prev;
        node -> next = where;
        node -> prev = where -> prev;
        where -> prev = node;
        help -> next = node;
    }
    void Insert(TNode* where, TList& other)
    {
        if ((where == first)&&(where == last))
        {
            TList(other);
        }
        else if (where == first)
             {
                 where -> prev = other.LastNode();
                 first = other.FirstNode();
             }
             else
             {
                 TNode* temp = where -> prev;
                 where -> prev = other.LastNode();
                 temp -> next = other.FirstNode();
             }
        other.Delete(other.FirstNode(), other.LastNode());

    }
    int PopLast()
    {
        TNode* help = last;
        int key = help -> key;
        last = help -> prev;
        Delete(help);
        return(key);
    }
    int PopFirst()
    {
        TNode* help = first;
        int key = help -> key;
        first = first -> next;
        Delete(help);
        return(key);
    }
    TNode* ExtractLast()
    {
        TNode* help = LastNode();
        TNode* res;
        res -> key = help -> key;
        res -> next = help -> next;
        res -> prev = help -> prev;
        last = last -> prev;
        Delete(help);
        return(res);
    }
    TNode* ExtractFirst()
    {
        TNode* help = FirstNode();
        TNode* res;
        res -> key = help -> key;
        res -> next = help -> next;
        res -> prev = help -> prev;
        first = first -> next;
        Delete(help);
        return(res);
    }
    TNode* Extract(TNode* node)
    {
        if (node == first)
        return(ExtractFirst());
        if (node == last)
        return(ExtractLast());
        TNode* help = node;
        TNode* res;
        res -> key = help -> key;
        res -> next = help -> next;
        res -> prev = help -> prev;
        Delete(help);
    }
    TList Extract(TNode* from, TNode* to)
    {
        TList res;
        for (TNode* i = from; i != to -> next; i = i -> next)
         {
             res.PushBack(i->key);
         }
        Delete(from,to);

        //from -> prev -> next = to -> next;
        //to -> next -> prev = from -> prev;
        return res;
    }
    void Delete(TNode* node)
    {
        if (first == last)
        first = last = NULL;
        else if (first == node)
             {
                 first = first -> next;
                 first -> prev = NULL;
             }
             else if (last == node)
                  {
                      last = last -> prev;
                      last -> next = NULL;
                  }
                  else
                  {
                      (node -> prev) -> next = node -> next;
                      (node -> next) -> prev = node -> prev;
                  }
        delete node;
        --size;

    }
    void Delete(TNode* from, TNode* to)
    {
        if (from == to)
        {
            Delete(from);

        }
        else
        {
            TNode* node = from -> next;
            for (;node != to -> next; node = node -> next)
              Delete(node -> prev);
            Delete(node->prev);
        }

    }
    void Print()
    {
        for (TNode* i =first; i != NULL; i = i -> next)
         cout << i -> key << ' ';
        cout << endl;
    }

};
int main()
{
    TList List;
    cout << "Sdelaem spisok iz 10 elementov" << endl;
    for (int i = 0; i < 10; ++i)
       List.PushBack(i);
    List.Print();

    cout << "Vstavim v nachalo chislo 123" << endl;
    List.PushFront(123);
    List.Print();

    cout << "Razdelim na 2 spiska" << endl;
    TNode* i = (List.FirstNode()) -> next;
    TNode* j = (List.LastNode()) -> prev;
    TList List1 = List.Extract(i,j);
    List1.Print();
    List.Print();

    cout << "Sdelayem  spisok iz  1, 2 , n-1 , n elementov 1ogo spiska" << endl;
    cout << "Udalim 1,2,n-1,n elementy iz pervogo spiska" << endl;
    TList List2 = List1;
    i = (List2.FirstNode()) -> next -> next;
    j = (List2.LastNode()) -> prev -> prev;
    List2.Delete(i,j);
    List2.Print();
    List1.Delete(List1.FirstNode());
    List1.Delete(List1.FirstNode());
    List1.Delete(List1.LastNode());
    List1.Delete(List1.LastNode());
    List1.Print();
    List.Print();
    return 0;
}

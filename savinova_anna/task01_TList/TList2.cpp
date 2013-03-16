#include <iostream>
using namespace std;

template <typename T>
struct TNode
{
        T val;
        TNode<T>* prev, next;
        TNode()
        {
                prev = 0;
                next = 0;
        };
        ~TNode<T>()
        {
        };
};

template <typename T>
class Myiterator
{
        TNode<T>* val;
};

template <typename T>
class TList
{
        TNode* first;
        TNode* last;
public:
        typedef Myiterator iterator;
        TList()
        {
                first = 0;
                last = 0;
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
};

int main()
{
        
        return 0;
}

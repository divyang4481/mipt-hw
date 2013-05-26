#include <iostream>
using namespace std;

template <typename T>
class TList
{
        struct TNode
        {
                T Val;
                TNode *Prev, *Next;
                explicit TNode():Val(0), Prev(0), Next(0){};
                TNode(T val): Val(val), Prev(0), Next(0){};
                TNode(T val, TNode* prev, TNode* next): Val(val), Prev(prev), Next(next){};
                ~TNode(){}
                TNode& operator = (TNode& oth)
                {
                        Val = oth.Val;
                        Prev = oth.Prev;
                        Next = oth.Next;
                        return *this;
                }
        };
public:
        class iterator
        {
                TNode* Node;
        public:
                iterator ()
                {
                        Node = 0;
                }
                iterator (TNode* nd)
                {
                        Node = nd;
                }
                iterator (const iterator& it)
                {
                        TNode* nd = new TNode;
                        nd -> Val = it.Node -> Val;
                        nd -> Prev = it.Node -> Prev;
                        nd -> Next = it.Node -> Next;
                        Node = nd;
                        delete nd;
                }
                const iterator& operator++()
                {
                        Node = Node -> Next;
                        return *this;
                }
                iterator operator + (int n) const
                {
                        iterator tmp = *this;
                        for (int i = 0; i < n; ++i)
                                ++tmp;
                        return tmp;
                }
                const iterator& operator--()
                {
                        Node = Node -> Prev;
                        return *this;
                }
                T& operator *()
                {
                        return Node -> Val;
                }
                bool operator == (const iterator& it)
                {
                        if (Node == it.Node)
                                return true;
                        return false;
                }
                bool operator != (const iterator& it)
                {
                        if (!(*this == it))
                                return true;
                        return false;
                }
                iterator& operator = (const iterator& it)
                {
                        *Node = *(it.Node);
                        return *this;
                }
                TNode* node()
                {
                        return Node;
                }
        };
        class const_iterator
        {
                TNode* Node;
        public:
                const_iterator ()
                {
                        Node = 0;
                }
                const_iterator (TNode* nd)
                {
                        TNode* tmp = nd;
                        Node = tmp;
                }
                const_iterator (const const_iterator& it)
                {
                        *Node = *(it.Node);
                }
                const const_iterator& operator++()
                {
                        Node = Node -> Next;
                        return *this;
                }
                const_iterator operator + (int n) const
                {
                        const_iterator tmp = *this;
                        for (int i = 0; i < n; ++i)
                                ++tmp;
                        return tmp;
                }
                const const_iterator& operator--()
                {
                        Node = Node -> Prev;
                        return *this;
                }
                const T& operator *() const
                {
                        return Node -> Val;
                }
                bool operator == (const const_iterator& it)
                {
                        if (Node == it.Node)
                                return true;
                        return false;
                }
                bool operator != (const const_iterator& it)
                {
                        if (!(*this == it))
                                return true;
                        return false;
                }
                const_iterator& operator = (const const_iterator& it)
                {
                        *Node = *(it.Node);
                        return *this;
                }
                TNode& node() const
                {
                        return Node;
                }
        };
private:
        TNode *First;
        TNode *Last;
public:
        TList<T> () {
                First = 0;
                Last = 0;
        }
        TList<T> (const TList &lst)
        {
                if (lst.First == 0)
                {
                        First = 0;
                        Last = 0;
                }
                TNode *p = new TNode(lst.First -> Val);
                First = p; 
                TNode *curp = lst.First -> Next;
                for (; curp; curp = curp -> Next, p = p -> Next)
                {
                        TNode* np = new TNode(curp -> Val, p, 0);
                        p -> Next = np;
                }
                Last = p;
        }
        ~TList()
        {
                clear();
        }
        bool empty() const
        {
                if (First) return false;
                return true;
        };
        void clear()
        {
                for (;Last;)
                {
                        TNode *p = Last -> Prev;
                        delete Last;
                        Last = p;
                }
                First = 0;
        }
        void swap(TList& oth)
        {
                std::swap(First, oth.First);
                std::swap(Last, oth.Last);
        }
        iterator begin()
        {
                iterator tmp(First);
                return tmp;
        }
        iterator end()
        {
                iterator tmp;
                return tmp;
        }
        const_iterator begin() const
        {
                const_iterator tmp(First);
                return tmp;
        }
        const_iterator end() const
        {
                const_iterator tmp;
                return tmp;
        }
        int front() const
        {
                return First -> Val;
        };
        int back() const
        {
                return Last -> Val;
        };
        int& front()
        {
                return First -> Val;
        };
        int& back()
        {
                return Last -> Val;
        };
        void push_back(T val)
        {
                TNode *p = new TNode(val);
                p -> Prev = Last;
                if (Last != 0)
                        Last -> Next = p;
                else First = p;
                Last = p;
        };
        void push_front(T val)
        {
                TNode *p = new TNode(val);
                p -> Next = First;
                if (First != 0)
                        First -> Prev = p;
                else Last = p;
                First = p;
        };
        int pop_back()
        {
                int val = Last -> Val;
                TNode* tmp = Last;
                Last = Last -> Prev;
                Last -> Next = 0;
                delete tmp;
                return val;
        };
        int pop_front()
        {
                int val = First -> Val;
                TNode* tmp = First;
                First = First -> Next;
                First -> Prev = 0;
                delete tmp;
                return val;
        };
        void insert(iterator where, T val)
        {
                TNode *p = new TNode(val);
                if (!First)
                {
                        First=p;
                        Last=p;
                        return;
                }
                p -> Prev = where.node();
                p -> Next = where.node() -> Next;
                p -> Next -> Prev = p;
                where.node() -> Next = p;
        };
        void erase(iterator iter)
        {
		TNode* tmp = iter.node();
                iter.node() -> Prev -> Next = iter.node() -> Next;
                iter.node() -> Next -> Prev = iter.node() -> Prev;
		delete tmp;
        };
        TList<T>& operator = (const TList<T>& oth)
        {
                clear();
                for (const_iterator it = oth.begin(); it != oth.end(); ++it)
                        push_back(*it);
                return *this;
        }
        void PrintStat(char name) const
        {
                cout << name << ": Empty: " << empty() << endl << "Elements: ";
                for (const_iterator it = begin(); it != end(); ++it)
                        cout << *it << " ";
                cout << endl;
        };
};

struct S
{
        static size_t Created;
        static size_t Deleted;
        S()
        {
                ++Created;
        }
        S(const S& oth)
        {
                ++Created;
        }
        ~S()
        {
                ++Deleted;
        }
};

size_t S::Created = 0;
size_t S::Deleted = 0;

int main()
{
        cout << "Create A" << endl;
        TList<int> A;
        A.PrintStat('A');
        cout << "Filling A" << endl;
        for (size_t i = 0; i < 35; ++i)
                A.push_back(i);
        A.PrintStat('A');
        cout << "Create B = A" << endl;
        TList<int> B = A;
        B.PrintStat('B');
        for (size_t i = 0; i < 5; ++i)
        {
                int tmp = A.pop_back();
                cout << "Pop_back: " << tmp << endl;
        }
        A.PrintStat('A');
        cout << "Swap A, B" << endl;
        A.swap(B);
        A.PrintStat('A');
        B.PrintStat('B');
        A.clear();
	A.PrintStat('A');
        cout << "A = B" << endl;
        A = B;
        A.PrintStat('A');
        cout << "Test iterator" << endl;
        TList<int>::iterator i = A.begin();
        cout << *i << endl;
        cout << "begin() + 4 = 17" << endl;
        *(i + 4) = 17;
        A.PrintStat('A');        
        for (TList<int>::iterator i = A.begin(); i != A.end(); ++i)
                cout << *i << " ";
        cout << endl;
        cout << "Test back() = 5" << endl;
        A.back() = 5;
        cout << "A.back() = " << A.back() << endl;
        A.PrintStat('A');
        cout << "Test insert insert(A.begin() + 5, 71)" << endl;
        A.insert(A.begin() + 5, 71);
        A.PrintStat('A');
        cout << "Test erase(A.begin() + 7)" << endl;
        A.erase(A.begin() + 7);
        A.PrintStat('A');
        cout << "Memory test" << endl;
        {
            TList<S> a;
            for (int i = 0; i < 10; ++i)
                a.push_back(S());

            TList<S> b = a;
            for (int i = 0; i < 10; ++i)
                b.push_back(S());

            //for (int i = 0; i < 10; ++i)
            //    b.pop_front();

            a.swap(b);

            TList<S> c;
            a = c;
            b.clear();
        }
        {
                TList<S> C;
                S tmp;
                for (int i = 0; i < 7; ++i)
                        C.push_back(tmp);                
        };
        cout << "Created: "<< S::Created << " Deleted: "<< S::Deleted << endl;
	return 0;
}

#include <iostream>
using namespace std;

template <typename T>
class TList {
        struct TNode {
                T value;
                TNode *prev, *next;
                explicit TNode():value(0), prev(0), next(0){};
                TNode(T val1): value(val1), prev(0), next(0){};
                TNode(T val1, TNode* prev, TNode* next): value(val1), prev(prev), next(next){};
                ~TNode(){}
                TNode& operator = (TNode& other) {
                        value = other.value;
                        prev = other.prev;
                        next = other.next;
                        return *this;
                }
        };
public:
        class iterator {
                TNode* Node;
        public:
                iterator () {

                }
                iterator (TNode* nd) {
                        Node = nd;
                }
                iterator (const iterator& other) {
                        TNode* nd = new TNode;
                        nd -> value = other.Node -> value;
                        nd -> prev = other.Node -> prev;
                        nd -> next = other.Node -> next;
                        Node = nd;
                        delete nd;
                }
                iterator& operator++() {
                        Node = Node -> next;
                        return *this;
                }
                iterator& operator--() {
                        Node = Node -> prev;
                        return *this;
                }
                iterator operator++(int) {
                        TNode* t = Node;
                        Node = Node -> next;
                        iterator* temp = new iterator(t);
                        return *temp;
                }
                iterator operator--(int) {
                        TNode* t = Node;
                        Node = Node -> prev;
                        iterator* tmp = new iterator(t);
                        return *tmp;
                }
                T& operator *() {
                        return Node -> value;
                }
                T* operator ->() {
                        return &(Node -> value);
                }
                bool operator == (const iterator& it) {
                        return (Node == it.Node);
                }
                bool operator != (const iterator& it)  {
                        return (!(*this == it));
                }
                iterator& operator = (const iterator& it){
                        *Node = *(it.Node);
                        return *this;
                }
                TNode* node() {
                        return Node;
                }
        };
        class const_iterator
        {
                TNode* Node;
        public:
                const_iterator () {
                        Node = NULL;
                }
                const_iterator (TNode* nd) {
                        TNode* temp = nd;
                        Node = temp;
                }
                const_iterator (const const_iterator& it) {
                        *Node = *(it.Node);
                }
                const const_iterator& operator++() {
                        Node = Node -> next;
                        return *this;
                }
                const const_iterator& operator--() {
                        Node = Node -> prev;
                        return *this;
                }
                const const_iterator operator++(int) {
                        TNode* t = Node;
                        Node = Node -> next;
                        const_iterator* tmp = new const_iterator(t);
                        return *tmp;
                }
                const const_iterator operator--(int) {
                        TNode* t = Node;
                        Node = Node -> prev;
                        const_iterator* tmp = new const_iterator(t);
                        return *tmp;
                }
                const T& operator *() const {
                        return Node -> value;
                }
                const T* operator ->() const {
                        return &(Node -> value);
                }
                bool operator == (const const_iterator& it) {
                        return (Node == it.Node);
                }
                bool operator != (const const_iterator& it) {
                        return (!(*this == it));
                }
                const_iterator& operator = (const const_iterator& it) {
                        *Node = *(it.Node);
                        return *this;
                }
                TNode& node() const {
                        return Node;
                }
        };
private:
        TNode *first;
        TNode *last;
public:
        TList<T> () {
                first = NULL;
                last = NULL;
        }
        TList<T> (const TList &lst) {
                if (lst.first == NULL) {
                        first = NULL;
                        last = NULL;
                }
                TNode *p = new TNode(lst.first -> value);
                first = p; 
                TNode *curp = lst.first -> next;
                for (; curp; curp = curp -> next, p = p -> next) {
                        TNode* np = new TNode(curp -> value, p, 0);
                        p -> next = np;
                }
                last = p;
        }
        ~TList() {
                clear();
        }
        bool empty() const {
                return first;
        };
        void clear() {
                for (;last;) {
                        TNode *p = last -> prev;
                        delete last;
                        last = p;
                }
                first = NULL;
        }
        void swap(TList& other) {
                swap(first, other.first);
                swap(last, other.last);
        }
        iterator begin() {
                iterator tmp(first);
                return tmp;
        }
        iterator end() {
                iterator tmp;
                return tmp;
        }
        const_iterator begin() const {
                const_iterator tmp(first);
                return tmp;
        }
        const_iterator end() const {
                const_iterator tmp;
                return tmp;
        }
        T front() const {
                return first -> value;
        }
        T back() const {
                return last -> value;
        }
        T& front() {
                return first -> value;
        }
        T& back() {
                return last -> value;
        }
        void push_back(T val1) {
                TNode *p = new TNode(val1);
                p -> prev = last;
                if (last != NULL)
                        last -> next = p;
                else first = p;
                last = p;
        }
        void push_front(T val1) {
                TNode *p = new TNode(val1);
                p -> next = first;
                if (first != NULL)
                        first -> prev = p;
                else last = p;
                first = p;
        }
        int pop_back() {
                int val1 = last -> value;
                TNode* tmp = last;
                last = last -> prev;
                last -> next = NULL;
                delete tmp;
                return val1;
        }
        int pop_front() {
                int val1 = first -> value;
                TNode* tmp = first;
                first = first -> next;
                first -> prev = NULL;
                delete tmp;
                return val1;
        }
        void insert(iterator& where, T val1) {
                TNode *p = new TNode(val1);
                if (!first) {
                        first=p;
                        last=p;
                        return;
                }
                p -> prev = where.node();
                p -> next = where.node() -> next;
                p -> next -> prev = p;
                where.node() -> next = p;
        }
        void erase(iterator& iter) {
                TNode* tmp = iter.node();
                iter.node() -> prev -> next = iter.node() -> next;
                iter.node() -> next -> prev = iter.node() -> prev;
                delete tmp;
        }
        TList<T>& operator = (const TList<T>& other) {
                clear();
                for (const_iterator it = other.begin(); it != other.end(); ++it)
                        push_back(*it);
                return *this;
        }
        void PrintStat(char name) const {
                cout << name << ": empty: " << empty() << endl << "elements: ";
                for (const_iterator it = begin(); it != end(); ++it)
                        cout << *it << " ";
                cout << endl;
        };
};



int main()
{

        return 0;
}

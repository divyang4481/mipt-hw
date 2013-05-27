#include <iostream>
#include <vector>
#include <list>
using namespace std;

template <typename T>
class TNode {
public: 
        T value;
        TNode<T>* prev;
        TNode<T>* next;
        TNode(TNode<T>* next1=NULL,TNode<T>* prev1=NULL,T val1=0) {
            next=next1;
            prev=prev1;
            val=val1;
        }
        ~TNode() {
        }
};

template <class T>
class TList {
private:
        int size;
        TNode<T>* first;
        TNode<T>* last;
public:
       class TIterator {
                TNode<T>* targ;
        public:
                TIterator() {
                        targ = NULL;
                }
                TIterator(TNode<T>* arg) {
                        targ = arg;
                }
                ~TIterator() {
                }
                TIterator& operator ++ () {
                        targ = targ->next;
                        return *this;
                }
                const TIterator operator ++ (int) {
                        TIterator a = *this;
                        targ = targ->next;
                        return a;
                }
                TIterator& operator -- () {
                        targ = targ->prev;
                        return *this;
                }
                const TIterator operator -- (int) {
                        TIterator a = *this;
                        targ = targ->prev;
                        return a;
                }
                T& operator * () {
                        return targ->val;
                }
                T* operator ->() {
                        return &(targ -> Val);
                }
                bool operator == (const TIterator& other) {
                        return (targ == other.targ);
                }
                bool operator != (const TIterator& other) {
                        return (targ != other.targ);
                }
                TIterator& operator = (const TIterator& other) {
                        targ = other.targ;
                        return *this;
                }
                TNode<T>* _myNode () {
                        return targ;
                }

        };
	   class TConst_Iterator {
                const TNode<T>* targ;
        public:
                TConst_Iterator() {
                        targ = NULL;
                }
                TConst_Iterator(const TNode<T>* arg) {
                        targ = arg;
                }
                ~TConst_Iterator() {
                }
                TConst_Iterator& operator ++ () {
                        targ = targ->next;
                        return *this;
                }
                const TConst_Iterator operator ++ (int) {
                        TConst_Iterator a = *this;
                        targ = targ->next;
                        return a;
                }
                TConst_Iterator& operator -- () {
                        targ=targ->prev;
                        return *this;
				}
                const TConst_Iterator operator -- (int) {
                        TConst_Iterator a = *this;
                        targ=targ->prev;
                        return a;
                }
                const T& operator * () const {
                        return targ->val;
                }
                const T* operator ->() const {
                        return &(Node -> Val);
                }
                bool operator == (const TConst_Iterator& other) {
                        return targ == other.targ;
                }
                bool operator != (const TConst_Iterator& other) {
                        return targ != other.targ;
                }
                TConst_Iterator& operator = (TConst_Iterator& other) {
                        targ = other.targ;
                        return *this;
                }

        };
 	
		TList<T> () {
            size = 0;
            first = NULL;
            last = NULL;
        }
        TList<T> (const TList<T>& other) {
                if (first == NULL) {
                        first = NULL;
                        last = NULL;
                } else {
					size = 0;
					first = NULL;
					last = NULL;
					const TNode* node = other.FirstNode();
					while (node != NULL) {
							PushBack(node->value);
							node = node->next;
					}
                }
        }
        ~TList<T> () {
			clear();
        }
        bool Empty () const {
                return first==NULL;
        }
        void clear() {
            for (; last;) {
                TNode *p = last -> prev;
                delete last;
                last = p;
            }
            first = NULL;
        }
        void Push_Back (T val) {
                TNode* node = new TNode;
                node->value = val;
                node->next = NULL;
                node->prev = last;
                if (last == NULL)
                        first = node;
                else
                        last->next = node;
                last = node;
                size++;
        }
        void Push_Front (T val) {
                TNode* node = new TNode;
                node->value = val;
                node->next = first;
                node->prev = NULL;

                if (first == NULL) 
                        last = node;
                else 
                        first->prev = node;
                first = node;
                size++;
        }
        T pop_front() {
            int val = first -> val;
            TNode* tmp = first;
            first = first -> next;
            first -> prev = NULL;
            delete tmp;
            return val;
        }
        T pop_back() {
            int val = last -> val;
            TNode* tmp = last;
            last = last -> prev;
            last -> next = NULL;
            delete tmp;
            return val;
        }
		void Swap(TList<T>& other) {
                swap(first, other.first);
                swap(last, other.last);
        }
        iterator begin() {
                return iterator tmp(First);
        }
        iterator end()
        {
                iterator tmp;
                return tmp;
        }
        T front() const
        {
                return first -> val;
        }
        T back() const
        {
                return last -> val;
        }
        T& front()
        {
                return first -> val;
        }
        T& back()
        {
                return last -> val;
        }
        void erase(iterator& iter) {
            TNode* tmp = iter.node();
            iter.node() -> prev -> next = iter.node() -> next;
            iter.node() -> next -> prev = iter.node() -> prev;
            delete tmp;
        };
        TList<T>& operator = (const TList<T>& oth) {
            clear();
            for (const_iterator it = oth.begin(); it != oth.end(); ++it)
                    push_back(*it);
            return *this;
        }
        void insert(iterator& where, T val) {
            TNode *p = new TNode(val);
            if (!first) {
                    first = p;
                    last = p;
                    return;
            }
            p -> prev = where.node();
            p -> next = where.node() -> next;
            p -> next -> prev = p;
            where.node() -> next = p;
        }

};

int main()
{
        
   
        return 0;
}
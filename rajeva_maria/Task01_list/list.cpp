#include <iostream>
using namespace std;
//template <typename T>
  /*struct TNode
        {
                T val;
                TNode<T> *prev;
                TNode<T> *next;
        public:
                TNode()
                {
                        val=0;
                        prev=0;
                        next=0;
                }
                TNode(T v)
                {
                        val=v;
                        prev=0;
                        next=0;
                }
                TNode(T v, TNode<T> *p, TNode<T> *n)
                {
                        val=v;
                        prev=p;
                        next=n;
                }
                ~TNode()
               // {cout << "lalala" << endl;}
				{

				};
                TNode& operator=(TNode&cop)
                {
                        val=cop.val;
                        next=cop.next;
                        prev=cop.prev;
                        return *this;
                }
        };*/
  //template <typename T>
  /*class TIterator
  {
                TNode<T> *node;
                private:
                TNode<T>* anode()
                        {
                                return node;
                        }
                public:
                        TIterator()
                        {
                                node=0;
                        }
                        explicit TIterator(TNode<T>* n)
                        {
                                node=n;
                        }
                        TIterator& operator ++()
                        {
                                node=node->next;
                                return *this;
                        }
                        TIterator& operator --()
                        {
                                node=node->prev;
                                return *this;
                        }
                        TIterator operator+(int n)
                        {
                                TIterator sum=*this;
                                for (int i=0; i<n;++i)
                                        ++sum;
                                return sum;
                        }
                        T& operator*()
                        {
                                return node->val;
                        }
                        bool operator == (const TIterator& iter )
                        {
                                return (node==iter.node);
                        }
                        bool operator != (const TIterator& iter)
                        {
                                return(!(node==iter.node));
                        }
                        TIterator& operator = (const TIterator& iter)
                        {
                                *node=*(iter.node);
                                return *this;
                        }
                       
  };*/
template <typename T>
        class TList
{
			struct TNode
        {
                T val;
                TNode *prev;
                TNode *next;
        public:
                TNode()
                {
                        val=0;
                        prev=0;
                        next=0;
                }
                TNode(T v)
                {
                        val=v;
                        prev=0;
                        next=0;
                }
                TNode(T v, TNode *p, TNode *n)
                {
                        val=v;
                        prev=p;
                        next=n;
                }
                ~TNode()
               // {cout << "lalala" << endl;}
				{

				};
                TNode& operator=(TNode&cop)
                {
                        val=cop.val;
                        next=cop.next;
                        prev=cop.prev;
                        return *this;
                }
        };
			
			class TIterator
			{
                TNode *node;
                public:
					TNode* anode()
                        {
                                return node;
                        }
                        TIterator()
                        {
                                node=0;
                        }
                        explicit TIterator(TNode* n)
                        {
                                node=n;
                        }
                        TIterator& operator ++()
                        {
                                node=node->next;
                                return *this;
                        }
                        TIterator& operator --()
                        {
                                node=node->prev;
                                return *this;
                        }
                        TIterator operator+(int n)
                        {
                                TIterator sum = *this;
                                for (int i=0; i<n;++i)
                                        ++sum;
                                return sum;
                        }
                        T& operator*()
                        {
                                return node->val;
                        }
                        bool operator == (const TIterator& iter )
                        {
                                return (node==iter.node);
                        }
                        bool operator != (const TIterator& iter)
                        {
                                return(!(node==iter.node));
                        }
                        TIterator& operator = (const TIterator& iter)
                        {
                                *node=*(iter.node);
                                return *this;
                        }
                       
  };
			
                TNode* last;
                TNode* first;
        public:
                typedef TIterator iterator;
                TList()
                {
                        last=0;
                        first=0;
                }
                TList(const TList<T>&lst)
                {
                        if (lst.first==0)
                        {
                                first=0;
                                last=0;
                        }
                        TNode<T> *p=new TNode<T>(lst.first->val);
                        first=p;
                        TNode<T> *nd=lst.first->next;
                        for(;nd;nd=nd->next,p=p->next)
                        {
                                TNode<T>* np=new TNode<T>(nd->val,p,0);
                                p->next=np;
                        }
                        last=p;
                }      
				bool empty() const
                {
                        return((last==0)&&(first==0));
                };
                void clear()
                {
                        while(last)
                        {
                                TNode *t=last->prev;
                                delete last;
                                last=t;
                        }
                        first = 0;
                };
                void swap(TList<T>&s)
                {
                        std::swap(first,s.first);
                        std::swap(last,s.last);
                };
                iterator begin()
                {
                        return iterator(first);
                }
                iterator end()
                {
                        iterator it;
                        return it;
                }
                T& back() // l.back() = 5;
                {
                        return last->val;
                }
                const T& back() const
                {
                        return last->val;
                }
                T& front()
                {
                        return first->val;
                };
                const T& front() const
                {
                        return first->val;
                }
                void push_back(T val)
                {
                        TNode *node=new TNode(val);
                        node->next=0;
                        if (first==0)
                        {
                                first=last=node;
                        }
                        else
                        {
                                node->prev=last;
                                last->next=node;
                                last = node;
                        }
                };
                void push_front(T val)
                {
                        TNode* t=new TNode;
                        t->val=val;
                        t->prev=0;
                        if (last==0)
                        {
                                last=first=t;
                                t->next=0;
                        }
                        else
                        {
                                t->next=first;
                                first->prev=t;
                                first=t;
                        }
                        return;
                };
                T pop_back()
                {
                        T val=last->val;
                        TNode*t=last;
                        last=last->prev;
						if (last)
							last->next=0;
						else first = 0;
                        delete t;
                        return val;
                };
                T pop_front()
                {
                        T val=first->val;
                        TNode*t=first;
                        first=first->next;
						if (first)
                        first->prev=0;
						else last=0;
                        delete t;
                        return val;
                       
                };
                void insert(TIterator& pos,T val )
                {
                        TNode *t=new TNode(val);
                        if (!first)
                        {
                                first=t;
                                last=t;
                                return;
                        }
                        t->prev=pos.anode();
                        t->next=pos.anode()->next;
                        t->next->prev=t;
						t->prev->next=t;
                        //pos.anode()->next=t;
                }                                            // void insert(TIterator pos, T val)
                                                                                                        // template<TOtherIter
                                                                                                        // void insert(TIterator pos, TOtherIter srcBeg, TOtherIter srcEndl)
               
                void erase(TIterator& it)
                {
                        TNode<T>* t=it.node();
                        it.anode()->prev->next=it.anode()->next;
                        it.anode()->next->prev=it.anode()->prev;
                        delete t;
                };
                TList& operator=(TList& cop)
                {
                        clear();
                        for (TIterator<T> it=cop.begin();it!=cop.end();++it)
                                push_back(*it);
                        return* this;
 
                }
        };
         template <typename T>
         void TPrint(TList<T>& list)
         {
               
                for (TList<T>::iterator iter=list.begin();iter!=list.end();++iter)
                        cout<<*iter;
                cout<<endl;
         };
       
 
 
int main()
{      
 
        TList<int> List;
        for (int i=0;i<10; i++)
                {
                        List.push_back(i);
                };
		 TList<int>::iterator tt=List.begin()+2;
		 List.insert(tt,1);
        TPrint(List);
        //TIterator<int> iter=List.begin();
        //cout<<List.empty();
        List.clear();
		cout<<List.empty()<<endl;
		for (int i=0;i<10; i++)
                {
                        List.push_front(i);
                };
		 TPrint(List);
		 cout<<List.empty()<<endl;
		 for (int i=0;i<9; i++)
			 cout << List.pop_back() << " ";
		 cout << endl;
		 List.pop_front();
		 cout<<List.empty();
		 TList<int>::iterator t=List.begin();//+2;
		 //List.insert(tt,1);
		// int a = *tt;
		 //cout << a;
		 //TList<int> A(List);

        /*const TList<int> A(List);
        TList<int>B=A;
        B.clear();
        B.swap(List);
       
        List.push_back(1);
        List.push_back(1);
        ///cout<<endl;
        cout<<*List.begin();
        TPrint(List);*/
        system("pause");
        return 0;
}
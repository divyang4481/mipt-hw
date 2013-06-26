#include <iostream>
using namespace std;

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
                        TNode *p=new TNode(lst.first->val);
                        first=p;
                        TNode *nd=lst.first->next;
                        for(;nd;nd=nd->next,p=p->next)
                        {
                                TNode* np=new TNode(nd->val,p,0);
                                p->next=np;
                        }
                        last=p;
                }   
				~TList()
				{
					clear();
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
                      
                }                                           
                                                                                                        
               
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
                        for (iterator it=cop.begin();it!=cop.end();++it)
                                push_back(*it);
                        return* this;
 
                }
        };
         template <typename T>
         void TPrint(TList<T>& list)
         {
               
                for (TList<T>::iterator iter=list.begin();iter!=list.end();++iter)
                        cout<<*iter<<' ';
                cout<<endl;
         };

		 struct TFoo {
  static int Created;
  static int Deleted;

  TFoo() { ++Created; }
  TFoo(const TFoo&) { ++Created; }
  ~TFoo() { ++Deleted; }
};

int TFoo::Created = 0;
int TFoo::Deleted = 0;
       
 
 
int main()
{      
 
        TList<int> List;
		cout<<"empty: "<<List.empty()<<endl;
		for (int i=0;i<10; i++)
                {
                        List.push_back(i);
                };
		cout<<"elements: "<<endl;
		TPrint(List);
		cout<<"empty: "<<List.empty()<<endl;
		TList <int> List1 (List);
		List1.clear();
		cout<<"empty after clear: ";
		cout<<List1.empty()<<endl;
		List.swap(List1);
		cout<<"elements after swap: "<<endl;
		TPrint(List1);
		cout<<"front: "<<List1.front()<<endl;
		cout<<"back: "<<List1.back()<<endl;
		List1.push_back(10);
		cout<<"elements after pushback: ";
		TPrint(List1);
		List1.push_front(-1);
		cout<<"elements after pushfront:";
		TPrint(List1);
		List1.pop_back();
		cout<<"elements after popback: ";
		TPrint(List1);
		List1.pop_front();
		cout<<"elements after pushfront:";
		TPrint(List1);
		TList<int>::iterator it=List1.begin()+4;
		List1.insert(it,100);
		cout<<"elements after insert: ";
		TPrint(List1);
		List=List1;
		cout<<"elements after operator = ";
		TPrint(List);
		{
            TList<TFoo> a;
            for (int i = 0; i < 10; ++i)
                a.push_back(TFoo());

           TList<TFoo> b = a;
           for (int i = 0; i < 10; ++i)
               b.push_back(TFoo());

            a.swap(b);

            TList<TFoo> c;
            a = c;
        }
       cout<<endl<<"created: "<<TFoo::Created<<endl;
	   cout<<"deleted: "<<TFoo::Deleted<<endl;
		system("pause");
        return 0;
}
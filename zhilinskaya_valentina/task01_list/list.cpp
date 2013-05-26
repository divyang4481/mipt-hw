# include <iostream>
# include <stdlib.h>
using namespace std;

struct leak {
	static int Created;
	static int Deleted;
	leak() {++Created;}
	leak (const leak&) {++Created;}
	~leak() {++Deleted;}
};

int leak :: Created = 0;
int leak :: Deleted = 0;
template <class T>
class TNode {
public:
        TNode<T>* next;
        TNode<T>* prev;
        T val;
        TNode(TNode<T>* new_next = NULL, TNode<T>* new_prev = NULL, T new_val = T()) 
		{
			next = new_next;
			prev = new_prev;
			val = new_val;
		}
		~TNode() {}
};
template <class T>
class TList
{
private:
	TNode<T>* first;
	TNode<T>* last;
	TNode<T>* elem;
public:
	class TConst_Iterator
	{
	private:
		const TNode<T>* node;
	public:
		TConst_Iterator() { node = NULL;}
		TConst_Iterator(const TNode<T>* new_node) { node = new_node;}
		~TConst_Iterator() {}
		const T& operator* () { return node->val;}
		bool operator== (const TConst_Iterator& other) { return node == other.node;}
		bool operator!= (const TConst_Iterator& other) { return node != other.node;}
		TConst_Iterator& operator= (TConst_Iterator& other) { node = other.node; return *this;}
		TConst_Iterator& operator++ () {node = node->next; return *this;}
		const TConst_Iterator operator++ (int) 
		{
			TConst_Iterator old_node = *this;
			node = node->next;
			return old_node;
		}
		TConst_Iterator& operator-- () {node = node->prev; return *this;}
		const TConst_Iterator operator-- (int) 
		{
			TConst_Iterator old_node = *this;
			node = node->prev;
			return old_node;
		}
	};
	class TIterator 
	{
	private:
		TNode<T>* node;
	public:
		TIterator() { node = NULL;}
		TIterator(TNode<T>* new_node) { node = new_node;}
		~TIterator() {}

		T& operator* () { return node->val;}
		bool operator== (const TIterator& other) { return node == other.node;}
		bool operator!= (const TIterator& other) { return (node != other.node);}
		TIterator& operator= (const TIterator& other) { node = other.node; return *this;}
		TIterator& operator++ () { node = node->next; return *this;}
		const TIterator operator++ (int) 
		{
			TIterator old_node = *this;
			node = node->next;
			return old_node;
		}
		TIterator& operator-- () { node = node->prev; return *this;}
		const TIterator operator-- (int) 
		{
			TIterator old_node = *this;
			node = node->prev;
			return old_node;
		}
		TNode<T>* getNode () { return node;}
		T getVal () { return node->val;}
		operator TConst_Iterator() { return TConst_Iterator(node);}
	};
	TList<T>()
	{
		first = NULL;
		last = NULL;
		elem = new TNode<T>;
	}
	TList<T>(int size, const T& n)
	{
        first = NULL;
        last = NULL;
		elem = new TNode<T>;
        for (int i = 0;i < size; ++i)
            push_back(n);
    }
	TList<T>(const TList<T>& other)
	{
		first = NULL;
		last = NULL;
		elem = new TNode<T>;
		for (typename TList<T>::TConst_Iterator it = other.begin(); it!= other.end(); ++it)
			push_back(*it);
	}
	~TList<T>()
	{
		if (first != NULL) 
		{
			TNode<T>* other;
			do {
				other = first;
				first = first->next;
				delete other;
			}
			while (first);
		}
		else
			delete elem;
		first = NULL;
		last = NULL;
		elem = NULL;
	}
	bool empty() const
	{
		return (first == NULL);
    }
	void clear()
	{
        while (!empty())
            pop_back();
	}
	void swap(TList<T>& other)
	{
		std::swap(first, other.first);
		std::swap(last, other.last);
		std::swap(elem, other.elem);
	}
	TIterator begin()
	{
		if (first) return TIterator(first);
		return TIterator(elem);
	}
	TConst_Iterator begin() const
	{
		if (first) return TConst_Iterator(first);
		return TConst_Iterator(elem);
	}
	TIterator end () { return TIterator(elem);}
	TConst_Iterator end () const { return TConst_Iterator(elem);}
	T back() const { return last->val;}
	T front() const { return first->val;}
	void push_back(T new_val)
	{
		TNode<T>* new_node = new TNode<T> (elem, last, new_val);
		elem->prev = new_node;
		if (this->empty()) 
		{
			first = new_node;
			last = new_node;
		}
		else 
		{
			last->next = new_node;
			last = new_node;
		}
	}
	void push_front(T new_val)
	{
		TNode<T>* new_node = new TNode<T> (first, NULL, new_val);
		if (this->empty()) {
			first = new_node;
			last = new_node;
			elem->prev = last;
			last->next = elem;
		}
		else {
			first->prev = new_node;
			first = new_node;
		}
	}
	void pop_back()
	{
		if (first == NULL) return;
		if (first == last)
		{
			delete first;
			first = NULL;
			last = NULL; 
			elem->prev = NULL;
			return;
		}
		TNode<T>* temp = last;
        last = last->prev;
        last->next = elem;
        elem->prev = last;
        delete temp;
	}
	void pop_front()
	{
		if (first == NULL) return;
		if (first == last)
		{
			delete first;
			first = NULL;
			last = NULL; 
			elem->prev = NULL;
			return;
		}
		TNode<T>* temp = first;
        first = first->next;
        first->prev = 0;
		delete temp;
	}
	TIterator insert(TIterator pos, const T& new_val)
	{
		if (pos.getNode() == first)  
		{
			TNode<T>* new_node = new TNode<T>(first, NULL, new_val);
			first->prev = new_node;
			first = new_node;
			return --pos;
		}
		if (pos.getNode() == elem) 
		{
			this->push_back(new_val);
			return --pos;
		}
		TIterator temp = pos--;
		TNode<T>* new_node = new TNode<T>(temp.getNode(), pos.getNode(), new_val);
		temp.getNode()->prev = new_node;
		pos.getNode()->next = new_node;
		return ++pos;
	}
	TIterator insert(TIterator pos, int n, const T& new_val)
	{
		for (int i = 0; i < n; ++i)
			this->insert(pos, new_val);
		return pos;
	}
	TIterator insert(TIterator pos, TConst_Iterator beg, TConst_Iterator end)
	{
		for (; beg != end; ++beg)
			this->insert(pos, *beg);
		return pos;
	}
	TIterator erase(TIterator pos)
	{
		if (pos == first)
		{
			++pos;
			this->pop_front();
			return pos;
		}
		if (pos == last)
		{
			++pos;
			this->pop_back();
			return pos;
		}
		typename TList<T>::TIterator it = pos;
		++it;
		TNode<T>* from = pos.getNode()->prev;
		TNode<T>* to = pos.getNode()->next;
		from->next = to;
		to->prev = from;
		delete pos.getNode();
		return it;
	}
	TIterator erase(TIterator beg, TIterator end)
	{
		TIterator iter = beg;
		while (iter != end) 
			iter = erase(iter);
		return iter;
	}
	TIterator splice(TIterator pos, TList<T>& list)
	{
		insert(pos, list.begin(), list.end());
		list.clear();
		return pos;
	}
	TIterator splice(TIterator pos, TList<T>& list, TIterator iter)
	{
		insert(pos, iter.getVal());
		list.erase(iter);
		return pos;
	}
	TIterator splice(TIterator pos, TList<T>& list, TIterator beg, TIterator end)
	{
		insert(pos, beg, end);
		list.erase(beg, end);
		return pos;
	}
	TList<T>& operator= (TList<T>& other)
	{
		this->clear();
		for (typename TList<T>::TIterator it=other.begin(); it!=other.end(); ++it)
		{
			this->push_back(*it);
		}
		return *this;
	}
};
template <class T>
void print (TList<T> list){
	TList <int>::TIterator iter;
	for (iter = list.begin(); iter != list.end(); ++iter)
		cout << iter.getVal() << " ";
	cout<<'\n';
}
int main()
{
	/*
	TList<int> my_list;
	cout << "TList<int> my_list;                    my_list empty?"; (my_list.empty())? cout << " yes\n": cout<<"no\n";
	TList<int> my_list2(5, 3);
	cout << "TList<int> my_list2(5, 3);             my_list2 empty?"; (my_list2.empty())? cout << " yes\n": cout<<"no\n";
	TList<int> my_list3(my_list2);
	cout << "TList<int> my_list3(my_list2);         my_list3 empty?"; (my_list3.empty())? cout << " yes\n": cout<<"no\n";
	my_list3.clear();
	cout << "my_list3.clear();                      my_list3 empty?"; (my_list3.empty())? cout << " yes\n": cout<<"no\n";
	cout << "my_list2: \n";
	print(my_list2);
	my_list.push_back(0);//0
	my_list.push_back(1);//01
	my_list.push_back(2);//012
	my_list.push_back(3);//0123
	cout << "my_list after push_back:\n"; 
	print(my_list);
	my_list.push_front(9);//90123
	my_list.push_front(8);//890123
	my_list.push_front(7);//7890123
	cout << "my_list after push_front:\n"; 
	print(my_list);
	my_list.pop_back();//789012
	cout << "my_list after pop_back:\n"; 
	print(my_list);
	my_list.pop_front();//89012
	my_list.pop_front();//9012
	my_list.pop_front();//012
	cout << "my_list after pop_front:\n"; 
	print(my_list);
	cout << "my_list2 = my_list:\n";
	my_list2 = my_list;
	print(my_list);
	print(my_list2);
	cout << "front = "<<my_list.front()<<"; back = "<< my_list.back()<<'\n';
	my_list.insert(++my_list.begin(), 10);// 0 10 1 2
	cout << "my_list.insert(++my_list.begin(), 10):\n";
	print(my_list);
	my_list.insert(++my_list.begin(), 4, 5);// 0 5 5 5 5 10 1 2
	cout << "my_list.insert(++my_list.begin(), 4, 5):\n";
	print(my_list);
	my_list.insert(++(++my_list.begin()), my_list2.begin(), my_list2.end());// 0 5 0 1 2 5 5 5 10 1 2
	cout << "my_list.insert(++(++my_list.begin()), my_list2.begin(), my_list2.end()):\n";
	print(my_list);
	swap(my_list, my_list2);
	cout << "swap lists: \n";
	cout << "my_list "; print(my_list); 
	cout << "my_list2 "; print(my_list2);
	my_list2.erase(my_list2.begin());//5 0 1 2 5 5 5 10 1 2
	my_list2.erase(++my_list2.begin());//5 1 2 5 5 5 10 1 2
	my_list2.erase(--(my_list2.erase(--my_list2.end())));//5 1 2 5 5 5 10 
	cout << "my_list2 after erase: \n";
	print(my_list2);
	my_list2.erase(++my_list2.begin(), --my_list2.end());//5 10
	cout << "my_list2.erase(++my_list2.begin(), --my_list2.end()): \n";
	cout << "my_list2:     "; print(my_list2);
	cout << "my_list       "; print(my_list);
	TList <int>::TIterator my_iter;
	my_iter = my_list2.splice(my_list2.begin(), my_list);
	cout << "my_list2.splice(my_list2.begin(), my_list);       ";print(my_list2);
	cout << "change my_list:  ";
	my_list.push_back(1);
	my_list.push_back(2);
	my_list.push_back(3);
	print(my_list);
	cout << "my_list2:        "; print(my_list2);
	my_iter = my_list.splice(my_list.begin(), my_list2, my_list2.begin());
	cout << "my_list.splice(my_list.begin(), my_list2, my_list2.begin()): \n";
	cout << "my_list:  "; print(my_list);
	cout << "my_list2: "; print(my_list2);
	my_iter = my_list.splice(my_list.begin(), my_list2, my_list2.begin(), ++++my_list2.begin());
	cout << " my_list.splice(my_list.begin(), my_list2, my_list2.begin(), ++++my_list2.begin()): \n";
	cout << "my_list:  "; print(my_list);
	cout << "my_list2: "; print(my_list2);*/

	//_____________________________________________________________LEAK
	{	
		cout << "\n push_back + def.constr.";
		TList<leak> my_list;
		leak z;
		for (int i = 0; i< 5; ++i)
			my_list.push_back(z);
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{	
		cout << "\n push_back + pop_back + def.constr.";
		TList<leak> my_list;
		leak z;
		for (int i = 0; i < 10; ++i)
			my_list.push_back(z);
		for (int i = 0; i< 6; ++i)
			my_list.pop_back();
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{	
		cout << "\n push_front + pop_front+ def.constr.";
		TList<leak> my_list;
		leak z;
		for (int i = 0; i < 10; ++i)
			my_list.push_front(z);
		for (int i = 0; i< 6; ++i)
			my_list.pop_front();
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{	
		cout << "\n constr.  + empty  + back + front + end + begin (dont change (except constr.))";
		leak z;
		TList<leak> my_list(10, z);
		my_list.empty();
		z = my_list.back();
		z = my_list.front();
		my_list.end(); my_list.begin();
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{
		cout << "\n constr.cop. + swap";
		leak z;
		TList<leak> my_list(5, z);
		TList<leak> my_list2(my_list);
		my_list.swap(my_list2);
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{
		cout << "\n constr. + clear";
		leak z;
		TList<leak> my_list(5, z);
		my_list.clear();
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{
		cout << "\n constr. + insert";
		leak z;
		TList<leak> my_list(6, z);
		my_list.insert(my_list.begin(), z);
		my_list.insert(my_list.begin(), z);
		my_list.insert(my_list.begin(), z);
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{
		cout << "\n constr. + erase";
		leak z;
		TList<leak> my_list(10, z);
		my_list.erase(my_list.begin());
		my_list.erase(my_list.begin());
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{
		cout << "\n constr. + op=";
		leak z;
		TList<leak> my_list(5, z);
		TList<leak> my_list2(9, z);
		my_list2 = my_list;
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{
		cout << "\n constr. + splice";
		leak z;
		TList<leak> my_list(5, z);
		TList<leak> my_list2(9, z);
		my_list.splice(my_list.begin(), my_list2);
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	
	system ("pause");
	return 0;
}
/*
vertex - black or red
list - black (NULL)
red vertex: black right, black left
all ways(root->list): the same number of black vertex 
*/
#include <iostream>
#include <queue>

using namespace std;

struct leak
{
	int k;
	static int Created;
	static int Deleted;
	leak (int k1 = 0) : k(k1) {++Created;}
	leak (const leak& l2) {k = l2.k; ++Created;}
	~leak() {++Deleted;}
	bool operator< (const leak& other) const { return k < other.k;}
};
int leak::Created = 0;
int leak::Deleted = 0;

using namespace std;

enum TColor //ks ​​are assigned in the order (starting from zero)
{
	BLACK, 
	RED
};

template <class T>      
struct TNode
{
	TNode<T>* parent;
	TNode<T>* left;
	TNode<T>* right;
	TColor color;
	T key;
	TNode(TNode<T>* parent2 = NULL, TNode<T>* left2 = NULL, TNode<T>* right2 = NULL, TColor color2 = BLACK, T key2 = T())
		: parent(parent2), left(left2), right(right2), color(color2), key(key2)
	{}
};

template <class T, class TCompare = less <T> >
class TRBTree 
{
private:          
	TNode<T>* root;
	TCompare cmp;
	int size;

	void left_Rotate (TNode<T>* x) 
	{
		if ((x == NULL) || (x->right == NULL))
			return;
		TNode<T>* y = x->right;
		x->right = y->left;
		if (x->right != NULL)
			x->right->parent = x;
		y->parent = x->parent;
		if (x->parent == NULL)
			root = y;
		else 
			if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
		y->left = x;
		x->parent = y;
	}
	void right_Rotate (TNode<T>* x) 
	{
		if (x->left == NULL)
			return;
		TNode<T>* y = x->left;
		x->left = y->right;
		if (x->left != NULL)
			x->left->parent = x;
		y->parent = x->parent;
		if (x->parent == NULL) 
			root = y;
		else 
			if (x == x->parent->left) 
				x->parent->left = y;
			else 
				x->parent->right = y;
		y->right = x;
		x->parent = y;
	}
	void RB_Delete_Fixup (TNode<T>* x, TNode<T>* y)
	{
		while((!x && root) || (x != root && x->color == BLACK))//1 (korm)
		{
			if(x == y->left)//2
			{
				TNode<T>* w;
				w = y->right;//3
				if(w && w->color == RED) //4
				{
					w->color = BLACK;
					y->color = RED;
					left_Rotate(y);
					w = y->right;
				}
				if ((!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK)) //9
				{
					w->color = RED;
					x = y;
					y = y->parent;
				}
				else
				{
					if((!w->right) || (w->right->color == BLACK))//12
					{
						w->left->color = BLACK;
						w->color = RED;
						right_Rotate(w);
						w = y->right;
					}
					w->color = y->color;
					y->color = BLACK;
					if(w->right)
						w->right->color = BLACK;
					left_Rotate(y);
					x = root;
				}
			}
			else//22
			{
				TNode<T>* w;
				w = y->left;
				if(w && w->color == RED)
				{
					w->color = BLACK;
					y->color = RED;
					right_Rotate(y);
					w = y->left;
				}
				if ((!w->right || w->right->color == BLACK) && (!w->left || w->left->color == BLACK))
				{
					w->color = RED;
					x = y;
					y = y->parent;
				}
				else
				{
					if(!w->left || w->left->color == BLACK)
					{
						w->right->color = BLACK;
						w->color = RED;
						left_Rotate(w);
						w = y->left;
					}
					w->color = y->color;
					y->color = BLACK;
					if(w->left)
						w->left->color = BLACK;
					right_Rotate(y);
					x = root;
				}
			}
		}
		if(x)
			x->color = BLACK;
	}
	void RB_Insert_Fixup (TNode<T>* x) 
	{
		while (x->parent  && x->parent->color == RED) 
		{
			if (x->parent->parent->left && x->parent == x->parent->parent->left) 
			{
				TNode<T>* y = x->parent->parent->right;
				if (y && y->color == RED) 
				{
					x->parent->color = BLACK;
					y->color = BLACK;
					x->parent->parent->color = RED;
					x = x->parent->parent;
				}
				else 
				{
					if (x == x->parent->right) 
					{
						x = x->parent;
						left_Rotate(x);
					}
					x->parent->color = BLACK;
					x->parent->parent->color = RED;
					right_Rotate(x->parent->parent);
				}
			} 
			else 
			{
				TNode<T>* y = x->parent->parent->left;
				if (y && y->color == RED) 
				{
					x->parent->color = BLACK;
					y->color = BLACK;
					x->parent->parent->color = RED;
					x = x->parent->parent;
				}
				else 
				{
					if (x == x->parent->left) 
					{
						x = x->parent;
						right_Rotate(x);
					}
					x->parent->color = BLACK;
					x->parent->parent->color = RED;
					left_Rotate(x->parent->parent);
				}
			}
		}
		root->color = BLACK;
	}
	TNode<T>* find_elem(TNode<T>* el, const T& key) const 
	{
		while (el && (cmp(key,el->key) || cmp(el->key,key)))
			if (cmp(key,el->key)) 
				el = el->left;
			else 
				el = el->right;
		return el;
	}
	TNode<T>* find_elem(const T& key) const { return find_elem(root, key); }
	TNode<T>* min() const { return min(root); }
	TNode<T>* max() const { return max(root); }
	TNode<T>* min(TNode<T>* elem) const 
	{
		if (elem != NULL)
			while(elem->left)
				elem = elem->left;
		return elem;
	}
	TNode<T>* max(TNode<T>* elem) const 
	{
		if (elem != NULL)
			while(elem->right)
				elem = elem->right;
		return elem;
	}
	TNode<T>* Tree_Successor(TNode<T>* elem) const 
	{
		if (elem == NULL) 
			return NULL;
		if (elem->right)
		{
			return min(elem->right);
		}
		while (elem->parent && elem == (elem->parent)->right) 
			elem = elem->parent;
		if (elem->parent != NULL) 
		{
			return (elem->parent);
		}
		return NULL;
	}
	TNode<T>* Tree_Predecessor(TNode<T>* elem) const 
	{
		if (elem == NULL) 
			return NULL; 
		if (elem->left) 
			return max(elem->left);
		if (elem == elem->parent->right) 
			return elem->parent;
		do 
		{
			elem = elem->parent;
		}while (elem->parent && elem == elem->parent->right);
		return elem;
	}
	//________________________________________________________________________________________________________________
public:
	class TIterator
	{
		friend class TRBTree;
		friend class TCIterator;
		TNode<T>* elem;
		TRBTree<T>* tree;

		TNode<T>* my_elem() { return elem;}
	public:
		TIterator() { elem = NULL;}
		TIterator (TNode<T>* elem2, TRBTree<T>* tree2): elem(elem2), tree(tree2) {}
		TIterator ( const TIterator& it){ elem = it.elem; tree = it.tree;}
		T& operator* (){return elem->key;}
		TIterator& operator= (const TIterator& it){ elem = it.elem; tree = it.tree; return *this;}
		TIterator& operator++ (){elem = tree->Tree_Successor(elem); return *this;}
		const TIterator operator++ (int){ TIterator it(*this); ++*this; return it;}
		TIterator& operator-- (){elem = tree->Tree_Predecessor(elem); return *this;}
		const TIterator operator-- (int){TIterator it(*this); --*this; return it;}
		bool operator== (const TIterator& it){ return ((elem == it.elem) && (tree == it.tree));}
		bool operator!= (const TIterator& it){ return ((elem != it.elem) || (tree != it.tree));}

	};
	class TCIterator
	{
		TNode<T>* elem;
		const TRBTree<T>* tree;
		friend class TRBTree;
	public:
		TCIterator() { elem = NULL;}
		TCIterator (TNode<T>* elem2, const TRBTree<T>* tree2): elem(elem2), tree(tree2){}
		TCIterator (const TCIterator& it) { elem = it.elem; tree = it.tree;}
		const T& operator* (){ return elem->key;}
		TIterator& operator= (const TCIterator& it) {elem = it.elem; tree = it.tree; return *this;}
		TCIterator& operator++ (){ elem = tree->Tree_Successor(elem); return *this;}
		const TCIterator operator++ (int) { TCIterator it(*this); ++*this; return it;}
		TCIterator& operator-- (){	elem = tree->Tree-Predecessor(elem); return *this;}
		const TCIterator operator-- (int) {	TCIterator it(*this); --*this; return it;}
		bool operator== (const TCIterator& it) const {return ((elem == it.elem) && (tree == it.tree));}
		bool operator!= (const TCIterator& it) const {return ((elem != it.elem) || (tree != it.tree));}	
	}; 

	TRBTree (): root(NULL), cmp(), size(0) {}
	TRBTree (const TRBTree<T>& tree) : root(NULL), cmp(tree.cmp), size(0)
	{ 
		for (typename TRBTree<T>::TCIterator it = tree.begin(); it != tree.end(); ++it)
			this->insert(*it);
	}
	~TRBTree () { clear();}
	TRBTree& operator= (const TRBTree<T>& tree)
	{
		clear();
		for (typename TRBTree<T>::TCIterator it = tree.begin(); it != tree.end(); ++it)
			insert(*it);
		return *this;
	}
	void swap (TRBTree<T>& tree) 
	{
		std::swap(root, tree.root);
		std::swap(size, tree.size);
		std::swap(cmp, tree.cmp);	
	}
	TIterator begin() { return TIterator(min(root), this);}
	TCIterator begin() const { return TCIterator(min(), this);}
	TIterator end() { return TIterator(NULL, this);}
	TCIterator end() const { return TCIterator(NULL, this);}

	bool empty() const { return (size == 0);}

	void clear () 
	{
		if (root != NULL) 
		{
			queue< TNode<T>* > tmp;
			TNode<T>* elem;
			tmp.push(root);
			while (!tmp.empty()) 
			{
				elem = tmp.front();
				tmp.pop();
				if (elem->left) 
					tmp.push(elem->left);
				if (elem->right) 
					tmp.push(elem->right);
				delete elem;
			}
			root = NULL;
			size = 0;
		}
	}

	void erase (const T& val) //Tree-Delete
	{
		TNode<T>* z = find(val).my_elem();
		if (z)
		{
			TNode<T>* y;
			if ((!z->left) || (!z->right))
				y = z;
			else
				y = Tree_Successor(z); 
			TNode<T>* x;
			if (y->left)
				x = y->left;
			else
				x = y->right;
			if (x)
				x->parent = y->parent;
			if (y->parent == NULL)
				root = x;
			else
				if (y == y->parent->left)
					y->parent->left = x;
				else
					y->parent->right = x;
			if (y != z)
				z->key = y->key;
			if (y->color == BLACK)
				RB_Delete_Fixup(x, y->parent);
			--size;
			delete y;
		}
	} 
	void insert (const T& key) //Tree-Insert
	{
		++size;
		TNode<T>* x = root, *y(NULL);
		while (x) 
		{
			y = x;
			if (cmp(key, x->key))  
				x = x->left;
			else 
				x = x->right;
		}
		TNode<T>* z = new TNode<T>();
		z->key = key;
		z->parent = y;
		z->color = RED;
		if (!y) 
			root = z;
		else 
		{
			if (cmp(key, y->key)) 
				y->left = z;
			else {y->right = z;}
		}
		RB_Insert_Fixup(z);
	}
	TIterator find (const T& elem) 
	{
		TNode<T>* tmp = root;
		tmp = find_elem(tmp, elem);
		return TIterator(tmp, this);
	}
	TCIterator find (const T& elem) const 
	{
		TNode<T>* tmp = root;
		tmp = find_elem(tmp, elem);
		return TCIterator(tmp, this);
	}	
	int get_size() {return size;}
};
template <class T>  
void about_tree(TRBTree<T> tree, int n = -1)
{
	cout <<"\n___________________\n";
	if (tree.empty())
	{
		if (n != -1) cout<<"tree"<<n<<": ";
		cout << "our tree is empty now\n";
		cout << "size = "<<tree.get_size()<<"\n";
		cout <<"___________________\n";
	}
	else
	{
		if (n != -1) cout<<"tree"<<n<<": ";
		TRBTree<int>::TIterator it = tree.begin(), it2 = tree.end();
		for (; it != it2; ++it)
			cout << *it<<" ";
		cout << "\n";
		cout << "size = " << tree.get_size()<<"\n";
		cout <<"___________________\n";
	}
}

int main()
{/*
	TRBTree<int> tree;
	tree.insert(1); 
	tree.insert(2); 
	tree.insert(3); 
	about_tree(tree, 0); //123
	tree.clear();
	about_tree(tree, 0); //0
	tree.insert(1); 
	tree.insert(2);
	tree.insert(3);
	tree.erase(2);
	tree.erase(7);
	about_tree(tree, 0); //13
	TRBTree<int> tree1(tree);
	TRBTree<int> tree2;
	tree2 = tree1;
	about_tree(tree2, 2);//13
	about_tree(tree1, 1);//13
	tree.insert(7);
	about_tree(tree, 0);//137
	tree1.insert(0);
	about_tree(tree1, 1);//013
	tree.swap(tree1);
	about_tree(tree, 0);//013
	about_tree(tree1, 1);//137
	int elem = 8;
	if (tree.find(elem) != tree.end())
		cout <<"tree has elem = " << elem << "\n";
	else
		cout <<"tree hasnt elem = " << elem << "\n";
	tree.clear();
	for (int i = 0; i < 10; ++i)
		tree.insert(i);
	about_tree(tree, 0);
	for (int i = 0; i < 10; ++i)
		tree.erase(i);
	if (tree.empty()) cout << "(after erase)empty\n";
	else cout << "(after erase)isnt empty\n";*/
	//_________________________________________________________LEAK
	{	
		cout << "\n insert + def.constr.";
		TRBTree<leak> my_tree;
		leak z;
		for (int i = 0; i < 5; ++i)
		{
			leak z(i);
			my_tree.insert(z);
		}
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{	
		cout << "\n insert + find + end + def.constr.";
		TRBTree<leak> my_tree;
		for (int i = 0; i < 5; ++i)
		{
			leak z(i);
			my_tree.insert(z);
		}
		if (my_tree.find(3) != my_tree.end()) {cout << "\n ye";}
		if (my_tree.find(7) == my_tree.end()) {cout << "\n no";}
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{	
		cout << "\n insert + erase + clear + empty + def.constr.";
		TRBTree<leak> my_tree;
		for (int i = 0; i < 5; ++i)
		{
			leak z(i);
			my_tree.insert(z);
		}
		for (int i = 0; i < 5; ++i)
		{
			leak z(i);
			my_tree.erase(z);
		}
		my_tree.clear();
		if (my_tree.empty()) cout << "\n empty";
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";
	{
		cout << "\n insert + swap + op= + begin + constr.(2)";
		TRBTree<leak> my_tree;
		for (int i = 0; i < 5; ++i)
		{
			leak z(i);
			my_tree.insert(z);
		}
		TRBTree<leak> my_tree2(my_tree);
		leak z(9);
		my_tree2.insert(z);
		my_tree = my_tree2;
		my_tree2.swap(my_tree);
		my_tree.begin();
	}cout << "\n Created: " << leak::Created <<"\n Deleted: "<<leak::Deleted <<"\n\n";


	system("pause");
	return 0;
}


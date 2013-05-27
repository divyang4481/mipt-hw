#pragma once
#include <iostream>

enum EColor{RED, BLACK};

template<typename T>
class TTree{
public:
	struct TNode {
		T key;
		TNode* left;
		TNode* right;
		TNode* parent;
		EColor color;
		TNode(): key(T()), left(0), right(0), parent(0), color(RED) {}
		explicit TNode(T srcval): key(srcval), left(0), right(0), parent(0), color(RED) {}
	};
	TNode *Root;
	TNode *Nil;
	void destroy(TNode* cur){
		if (cur != Nil){
			if (cur->left != Nil && cur->left) 
				destroy (cur->left);
			if (cur->right != Nil && cur->right)
				destroy (cur->right);
			delete cur;
		}
	}
	void Transplant(TNode* u, TNode* v){
		if (u->parent == Nil)
			Root = v;
		else{
			if (u == u->parent->left)
				u->parent->left = v;
			else u->parent->right = v;
		}
		if (v != Nil)
			v->parent = u->parent;
	}
	void RightRotate(TNode* x){
		TNode* y = x->left;
		x->left = y->right;
		if (y->right != Nil)
			y->right->parent = x;
		y->parent = x->parent;
		if (x->parent == Nil)
			Root = y;
		else {
			if (x == x->parent->right)
				x->parent->right = y;
			else x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}
	void LeftRotate(TNode* x){
		TNode* y = x->right;
		x->right = y->left;
		if (y->left != Nil)
			y->left->parent = x;
		y->parent = x->parent;
		if (x->parent == Nil)
			Root = y;
		else {
			if (x == x->parent->left)
				x->parent->left = y;
			else x->parent->right = y;
		}
		y->left = x;
		x->parent = y;                        
	}
	void InsertRebalance(TNode* x){
		while (x->parent->color == RED){
			if (x->parent == x->parent->parent->left){
				TNode* y = x->parent->parent->right;
				if (y->color == RED){
					x->parent->color = BLACK;
					y->color = BLACK;
					x->parent->parent->color = RED;
					x = x->parent->parent;
				}
				else{
					if (x == x->parent->right){
						x = x->parent;
						LeftRotate(x);
					}
					x->parent->color = BLACK;
					x->parent->parent->color = RED;
					RightRotate(x->parent->parent);
				}
			}
			else{
				TNode* y = x->parent->parent->left;
				if (y->color == RED)
				{
					x->parent->color = BLACK;
					y-> color = BLACK;
					x-> parent->parent->color = RED;
					x = x->parent->parent;
				}
				else 
				{
					if (x == x->parent->left)
					{
						x = x->parent;
						RightRotate(x);
					}
					x->parent->color = BLACK;
					x->parent->parent->color = RED;
					LeftRotate(x->parent->parent);
				}
			}
		}
		Root->color = BLACK;
	}
	void DeleteRebalance(TNode* node){
		while (node != Root && node->color == BLACK){
			if (node == node->parent->left){
				TNode* tmp = node->parent->right;
				if (tmp->color == RED){
					tmp->color = BLACK;
					node->parent->color = RED;
					LeftRotate(node->parent);
					tmp = node->parent->right;
				}
				if (tmp->left->color == BLACK && tmp->right->color == BLACK){
					tmp->color = RED;
					node = node->parent;
				}
				else{
					if (tmp->right->color == BLACK)
					{
						tmp->left->color = BLACK;
						tmp->color = RED;
						RightRotate(tmp);
						tmp = node->parent->right;
					}
					tmp->color = node->parent->color;
					node->parent->color = BLACK;
					tmp->right->color = BLACK;
					LeftRotate(node->parent);
					node = Root;
				}
			}
			else{
				TNode* tmp = node->parent->left;
				if (tmp->color == RED){
					tmp->color = BLACK;
					node->parent->color = RED;
					RightRotate(node->parent);
					tmp = node->parent->left;
				}
				if (tmp->right->color == BLACK && tmp->left->color == BLACK){
					tmp->color = RED;
					node = node->parent;
				}
				else{
					if (tmp->left->color == BLACK)
					{
						tmp->right->color = BLACK;
						tmp->color = RED;
						LeftRotate(tmp);
						tmp = node->parent->left;
					}
					tmp->color = node->parent->color;
					node->parent->color = BLACK;
					tmp->left->color = BLACK;
					RightRotate(node->parent);
					node = Root;
				}
			}

		}
		node->color = BLACK;
	}
	TNode* Minimum(TNode* start) const{
		if (start == Nil)
			return Nil;
		TNode* cur = start;
		while (cur->left != Nil)
			cur = cur->left;
		return cur;                        
	}
	TNode* Minimum() const{
		return Minimum(Root);
	}
	TNode* Maximum(TNode* start) const {
		if (start == Nil)
			return Nil;
		TNode* cur = start;
		while (cur->right != Nil)
			cur = cur->right;
		return cur;                        
	}
	TNode* Maximum() const{
		return Maximum(Root);
	}
public:
	class iterator{
		TNode* node;
		TNode* Nil;
	public:
		friend class TTree<T>;
		iterator(TNode* snode, TNode* nil){
			node = snode;
			Nil = nil;
		}
		iterator(){
			node = 0;
			Nil = 0;
		}
		iterator(const iterator& it){
			node = it.node;
			Nil = it.Nil;
		}
		iterator& operator++(){ //follower
				if (node->right != Nil){
					node = node->right;
					while(node->left != Nil)
						node = node->left;
					return *this;
				}
				for (; node->parent != Nil; node = node->parent)
				{
					if(node->parent->left == node)
					{
						node = node->parent;
						return *this;       
					}
				}
				node = Nil;
				return *this;
		}
		iterator operator++(int){ //follower
			iterator temp = *this;
			if (node->right != Nil){
				node = node->right;
				while(node->left != Nil)
					node = node->left;
				return temp;
			}
			for (; node->parent != Nil; node = node->parent)
			{
				if(node->parent->left == node)
				{
					node = node->parent;
					return temp;       
				}
			}
			node = Nil;
			return temp;
		}
		iterator& operator--(){ //predecessor, prefix
				if (node->left != Nil){
					for(; node->right != Nil; node = node->right);
					return *this;
				}
				for (;node->parent != Nil; node = node->parent){
					if(node->parent->right == node){
						node = node->parent;
						return *this;
					}             
				}
				node = Nil;
				return *this;
		}
		iterator operator--(int){ //predecessor, postfix
			iterator temp = *this;
			if (node->left != Nil){
				for(; node->right != Nil; node = node->right);
				return temp;
			}
			for (;node->parent != Nil; node = node->parent){
				if(node->parent->right == node){
					node = node->parent;
					return temp;
				}             
			}
			node = Nil;
			return temp;
		}
		T operator*(){
			return node->key;
		}
		bool operator== (const iterator& it){
			if (node == it.node)
				return true;
			return false;
		}
		bool operator!= (const iterator& it){
			if (!(*this == it))
				return true;
			return false;
		}
		iterator& operator= (const iterator& it){
			node = it.node;
			Nil = it.Nil;
			return *this;
		}
	};
	class const_iterator{
		TNode* node;
		TNode* Nil;
	public:
		friend class TTree<T>;
		const_iterator(TNode* snode, TNode* nil){
			node = snode;
			Nil = nil;
		}
		const_iterator(){
			node = 0;
			Nil = 0;
		}
		const_iterator(const const_iterator& it){
			node = it.node;
			Nil = it.Nil;
		}
		const_iterator& operator++(){
			if(node!=Nil){
				if (node->right != Nil){
					node = node->right;
					while(node->left != Nil)
						node = node->left;
					return *this;
				}
				for (; node->parent != Nil; node = node->parent){
					if(node->parent->left == node){
						node = node->parent;
						return *this;       
					}
				}
				node = Nil;
			}
			return *this;
		}
		const_iterator& operator++(int){ //follower
			if (node!=Nil){
				const_iterator temp = *this;
				if (node->right != Nil){
					node = node->right;
					while(node->left != Nil)
						node = node->left;
					return temp;
				}
				for (; node->parent != Nil; node = node->parent){
					if(node->parent->left == node){
						node = node->parent;
						return temp;       
					}
				}
				node = Nil;
				return temp;
			}
			return *this;
		}
		const_iterator& operator--(){ //predecessor, prefix
			if (node!=Nil){
				if (node->left != Nil){
					for(; node->right != Nil; node = node->right);
					return *this;
				}
				for (;node->parent != Nil; node = node->parent){
					if(node->parent->right == node){
						node = node->parent;
						return *this;
					}             
				}
				node = Nil;
			}
			return *this;
		}
		const_iterator& operator--(int){ //predecessor, postfix
			if (node!=Nil){
				const_iterator temp = *this;
				if (node->left != Nil){
					for(; node->right != Nil; node = node->right);
					return temp;
				}
				for (;node->parent != Nil; node = node->parent){
					if(node->parent->right == node){
						node = node->parent;
						return temp;
					}             
				}
				node = Nil;
				return temp;
			}
			return *this;
		}
		const T& operator*(){
			return node -> key;
		}
		bool operator==(const const_iterator& it){
			if (node == it.node)
				return true;
			return false;
		}
		bool operator !=(const const_iterator& it){
			if (!(*this == it))
				return true;
			return false;
		}
		const_iterator& operator=(const const_iterator& it){
			node = it.node;
			Nil = it.Nil;
			return *this;
		}
	};
private:
	void Insert(TNode* node){
		TNode* y = Nil;
		TNode* x = Root;
		while (x != Nil){
			y = x;
			if (node->key < x->key)
				x = x->left;
			else x = x->right;
		}
		node->parent = y;
		if (y == Nil)
			Root = node;
		else {
			if (node->key < y->key)
				y->left = node;
			else y->right = node;
		}
		node->left = Nil;
		node->right = Nil;
		node->color = RED;
		InsertRebalance(node);
	}
	void Delete(const TNode* node){	
		if (node == Nil){
			std::cout << "You can't delete Nil" << std::endl;
			return;
		}
		TNode* x;
		TNode* temp = const_cast<TNode*> (node);
		TNode* y = temp;
		EColor yColor = y->color;
		if (temp->left == Nil){
			x = temp->right;
			Transplant(temp, temp->right);
		}
		else{
			if (temp->right == Nil)
			{
				x = temp->left;
				Transplant(temp, temp->left);
			}
			else{
				y = const_cast<TNode*>(Minimum(temp->right));
				yColor = y->color;
				x = y->right;
				if (y->parent == temp)
					x->parent = y;
				else{
					Transplant(y, y->right);
					y->right = temp->right;
					y->right->parent = y;
				}
				Transplant(temp, y);
				y->left = temp->left;
				y->left->parent = y;
				y->color = temp->color;
			}
			if (yColor == BLACK && x != Nil)
				DeleteRebalance(x);
		}
		delete temp;
	}
	TNode* Find (const T& k) const{
		TNode* curr = Root;
		while (curr != Nil){
			if (curr->key == k)
				return curr;
			curr = (k < curr->key ? curr->left : curr->right);
		}
		return Nil;
	}
public:
	TTree(){
		Nil = new TNode;
		Nil->color = BLACK;
		Root = Nil;
	}
	TTree(const TTree<T>& other){
		Nil = new TNode;
		Nil->color = BLACK;
		Root = Nil;
		*this = other;
	}
	TTree& operator =(const TTree<T>& other){
		clear();
		for (const_iterator it = other.begin(); it != other.end(); ++it)
			insert(*(it));
		return *this;
	}
	~TTree(){
		if (Root != Nil)
			destroy(Root);
		delete Nil;
	}
	void swap(TTree<T>& other){
		std::swap(Root, other.Root);
		std::swap(Nil, other.Nil);
	}
	iterator begin(){
		iterator it(Minimum(), Nil);
		return it;
	}
	iterator end(){
		iterator it(Nil, Nil);
		return it;
	}
	const_iterator begin() const{
		const_iterator it(Minimum(), Nil);
		return it;
	}
	const_iterator end() const{
		const_iterator it(Nil, Nil);
		return it;
	}
	bool empty() const{
		return (Root == Nil);
	}
	void clear(){
		if (Root != Nil)
			destroy(Root);
		Root = Nil;
	}
	void erase(iterator it){
		Delete(it.node);
	}
	iterator find(const T& val){
		TNode* tmp = Find(val);
		iterator it(tmp, Nil);
		return it;
	}
	iterator insert(T val){
		TNode* node = new TNode(val);
		Insert(node);
		iterator it(node, Nil);
		return it;
	}
	void PrintTree() const{
		if (empty()){
			std::cout << "Empty" << std::endl;
			return;
		}
		for(const_iterator it = begin(); it != end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
};
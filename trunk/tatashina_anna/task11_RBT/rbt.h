#pragma once
#include <string>
#include <iostream>


enum EColor{RED, BLACK};

template <typename T>
class TRBTree {
public:
	struct TNode {
    friend class TRBTree;
        T key;
        TNode *parent;
        TNode *left;
        TNode *right;
        EColor clr;
        TNode(): key(T(0)), left(NULL), right(NULL), parent(NULL), clr(RED) {}
        explicit TNode(const TNode *a) {
			*this = *a;
        }
        explicit TNode(T a): key(a), left(0), right(0), parent(0), clr(RED) {}
        bool operator== ( TNode& a ) const {
			return (parent == a.parent && left == a.left && right == a.right && clr == a.clr && key == a.key);
        }
        bool operator!= (TNode& a) const {
			return !(*this == a);
        }
        TNode& operator= (TNode& a) {
            parent = a.parent;
            left = a.left;
            right = a.right;
            clr = a.clr;
            key = a.key;
        }
        };
    class iterator {
    friend class TRBTree;
        TNode *it;
        TNode *Nil;
    public:
        iterator(): it(), Nil() {
		}
        iterator (const TNode *i, const TNode *nil) {
            it = const_cast<TNode *>(i);
            Nil = const_cast<TNode *>(nil);
        }
        iterator (const iterator &other) {
            it = other.it;
            Nil = other.Nil;
        }

        iterator& operator++() {
            if (it->right != Nil) {
                it = it->right;
                while (it->left != Nil)
					it = it->left;
                return *this;
            }
            for (; it->parent != Nil; it = it->parent) {
                if (it->parent->left == it) {
                    it = it->parent;
                    return *this;
                }
            }
            it = Nil;
            return *this;
        }
        iterator& operator--() {
            if ( it->left != Nil) {
                while (it->right != Nil)
                        it = it->right;
                return  *this;
            }
            for (; it->parent != Nil; it = it->parent) {
                if (it->parent->right == it) {
                        it = it->parent;
                        return *this;
                }
            }
            it = Nil;
            return *this;
        }
        T& operator*() {
			return it->key;
        }
        bool operator== (const iterator &i) {
			return (it == i.it && Nil == i.Nil);
        }
        bool operator!= (const iterator &i) {
			return (it != i.it || Nil != i.Nil);
        }
        iterator& operator= (const iterator& a) {
            it = a.it;
            Nil = a.Nil;
            return *this;
        }
    };
    class const_iterator
    {
    friend class TRBTree;
            TNode *it;
            TNode *Nil;
    public:
        const_iterator():it(), Nil(){}
        const_iterator (const TNode *i, const TNode *nil) {
            it = const_cast<TNode *>(i);
            Nil = const_cast<TNode *>(nil);
        }
		const_iterator(const const_iterator& another) {
            it = another.it;
            Nil = another.Nil;
		}
		const_iterator& operator++() {
			if (it->right != Nil) {
                    it = it->right;
                    while (it->left != Nil)
				        it = it->left;
                    return *this;
                }
                for (; it->parent != Nil; it = it->parent) {
                    if (it->parent->left == it) {
                        it = it->parent;
                        return *this;
                    }
                }
                it = Nil;
                return *this;
		}
        const_iterator& operator--() {
            if ( it->left != Nil) {
                while (it->right != Nil)
                     it = it->right;
                return  *this;
            }
            for (;it->parent != Nil; it = it->parent) {
                if( it->parent->right == it) {
                    it = it->parent;
                    return *this;
                }
            }
            it = Nil;
            return *this;
        }
        const T& operator*() {
            return it->key;
        }
        bool operator== (const const_iterator& i) {
			return (it == i.it && Nil == i.Nil);
        }
        bool operator!= (const const_iterator& i) {
            return (it != i.it || Nil != i.Nil);
        }
        const_iterator& operator= (const const_iterator& a) {
            it = a.it;
            Nil = a.Nil;
            return *this;
        }
    };



private:
        TNode *Root;
        TNode *Nil;
        void Destroy(TNode *curr) {
            if (curr != Nil) {
                if (curr -> left != Nil && curr -> left) 
					Destroy (curr -> left);
                if (curr -> right != Nil && curr -> right)
					Destroy (curr -> right);
                delete curr;
            }
        }
        void Transplant(TNode *u, TNode *v) {
            if ( u->parent == Nil )
				Root = v;
            else if ( u == u->parent->left )
                u->parent->left = v;
            else
                u->parent->right = v;
            v->parent = u->parent;
        }
        void RightRotate(TNode *x) {
            if ( x->left == Nil )
                return;
            TNode* y = x->left;
            x->left = y->right;
            if (y->right != Nil)
                y->right->parent = x;
            y->parent = x->parent;
            if ( x->parent == Nil)
                Root = y;
            else if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
            y->right = x;
            x->parent = y;
        }

        void LeftRotate (TNode *x) {
            if ( x->right == Nil )
                return;
            TNode* y = x->right;
            x->right = y->left;
            if (y->left != Nil)
                y->left->parent = x;
            y->parent = x->parent;
            if (x->parent == Nil)
                Root = y;
            else if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
            y->left = x;
            x->parent = y;
        }
        const TNode* Minimum(TNode *t) const {
            if (t == 0) return 0;
            TNode* curr = t;
            while (curr->left != Nil)
                curr = curr->left;
            return curr;
        }
        const TNode* Maximum(TNode *t) const {
            if (t == 0) return 0;
            TNode *curr = t;
            while (curr->right != Nil)
                curr = curr->right;
            return curr;
        }
        TNode* Successor(const TNode *node) const {
            if (node == Nil) return 0;
            if (node->right != Nil) return Minimum(node->right);
            for (const TNode *curr = node->parent; curr->parent; curr = curr->parent)
                if (curr->parent->left == curr)
                    return curr->parent;
            return 0;
        }
        TNode* Predecessor(const TNode *node) const {
            if (!node) return 0;
            if (node->left != Nil) return Minimum(node->left);
            for (const TNode *curr = node->parent; curr->parent; curr = curr->parent)
                if (curr->parent->right == curr)
                        return curr->parent;
            return 0;
        }

        void Insert_Fixup (TNode *node) {
            while ( node->parent->clr == RED ) {
                if (node->parent == node->parent->parent->left) {
                    TNode *y =node->parent->parent->right;
                    if (y->clr == RED) {
                        node->parent->clr = BLACK;
                        y->clr = BLACK;
                        node->parent->parent->clr = RED;
                        node = node->parent->parent;
                    } else {
                        if (node == node->parent->right)
                        {
                                node = node->parent;
                                LeftRotate (node);
                        }
                        node->parent->clr = BLACK;
                        node->parent->parent->clr = RED;
                        RightRotate (node->parent->parent);
                    }
				} else {
                    TNode *y =node->parent->parent->left;
                    if (y->clr == RED) {
                        node->parent->clr = BLACK;
                        y->clr = BLACK;
                        node->parent->parent->clr = RED;
                        node = node->parent->parent;
                    } else {
                        if (node == node->parent->left) {
                            node = node->parent;
                            RightRotate (node);
                        }
                        node->parent->clr = BLACK;
                        node->parent->parent->clr = RED;
                        LeftRotate (node->parent->parent);
                    }
                }
            }
            Root->clr = BLACK;
        }

        void Delete_Fixup (TNode *x) {
            while (x != Root && x->clr == BLACK ) {
                if (x == x->parent->left ) {
                    TNode* w = x->parent->right;
                    if ( w->clr == RED ) {
                            w->clr = BLACK;
                            x->parent->clr = RED;
                            LeftRotate ( x->parent );
                            w = x->parent->right;
                        }
                    if ( w->left->clr == BLACK && w->right->clr == BLACK )                             {
                        w->clr = RED;
                        x = x->parent;
                        } else {
                            if (w->right->clr == BLACK ) {
                                w->left->clr = BLACK;
                                w->clr = RED;
                                RightRotate (w);
                                w = x->parent->right;
                            }
                            w->clr = x->parent->clr;
                            x->parent->clr = BLACK;
                            w->right->clr = BLACK;
                            LeftRotate(x->parent);
                            x = Root;
                        }
                } else {
                        TNode* w = x->parent->left;
                        if ( w->clr == RED ) {
                            w->clr = BLACK;
                            x->parent->clr = RED;
                            RightRotate (x->parent);
                            w = x->parent->left;
                        }
                        if ( w->right->clr == BLACK && w->left->clr == BLACK ) {
                            w->clr = RED;
                            x = x->parent;
                        } else {
                            if (w->left->clr == BLACK ) {
                                w->right->clr = BLACK;
                                w->clr = RED;
                                LeftRotate (w);
                                w = x->parent->left;
                            }
                            w->clr = x->parent->clr;
                            x->parent->clr = BLACK;
                            w->left->clr = BLACK;
                            RightRotate(x->parent);
                            x = Root;
                        }
                }
        }
        x->clr = BLACK;
        }
public:
        TRBTree() {
            Nil = new TNode;
            Nil->clr = BLACK;
            Root = Nil;
        }

        TRBTree(const TRBTree<T> &a) {
            *this = a;
        }
        ~TRBTree () {
            if (Root != Nil)
                    Destroy(Root);
            delete Nil;
        }
        TRBTree& operator= (const TRBTree<T> &other) {
            Destroy(Root);
            Root = Nil;
            for (const_iterator pos = other.begin(); pos != other.end(); ++pos)
                    insert(*pos);
            return *this;
        }

        void swap( TRBTree<T> &other) {
            std::swap (Root, other.Root);
            std::swap (Nil, other.Nil);
        }
        iterator begin() {
            return iterator(Minimum (Root), Nil);
        }
        const_iterator begin() const {
			return const_iterator(Minimum (Root), Nil);
        }
        iterator end() {
			return iterator(Nil, Nil);
        }
        const_iterator end() const {
			return const_iterator(Nil, Nil);
        }
        bool empty() const {
			return (Root == Nil);
        }
        void clear() {
            if (Root != Nil)
                Destroy (Root);
            Root = Nil;
        }
        iterator find(T k) {
            TNode *curr = Root;
            while (curr != Nil) {
                if (curr->key == k) return iterator(curr, Nil);
                curr = (k < curr->key) ? curr->left : curr->right;
            }
            return end();
        }
        std::pair<iterator, bool> insert (T v) {
            bool has = false;
            TNode *node = new TNode(v);
            TNode  *y = Nil;
            TNode  *x = Root;
            while ( x != Nil) {
                y = x;
                if (node->key < x->key)
				    x = x->left;
                else {
                    if (node->key == x->key) has = true;
                    x = x->right;
                }
            }
            if (!has)  {
                node->parent = y;
                if (y == Nil)
                        Root = node;
                else if ( node->key < y->key )
                        y->left = node;
                else
                        y->right = node;
                node->left = node->right = Nil;
                node->clr = RED;
                Insert_Fixup(node);
            }
            else
				delete node;
            return std::make_pair<typename TRBTree<T>::iterator, bool> (iterator(node, Nil), has);
        }
        iterator erase (iterator a) {
            TNode* node = a.it;
            ++a;
            TNode* x;
            TNode* y = node;
            int y_original_color = y->clr;
            if (node->left == Nil) {
                x = node->right;
                Transplant(node, node->right);
            }
            else if (node->right == Nil) {
                x = node->left;
                Transplant(node, node->left);
            } else {
                y = const_cast<TNode*>( Minimum(node->right) );
                y_original_color = y->clr;
                x = y->right;
                if ( y->parent == node )
                        x->parent = y;
                else {
                    Transplant(y, y->right);
                    y->right = node->right;
                    y->right->parent = y;
                }
                Transplant(node, y);
                y->left = node->left;
                y->left->parent = y;
                y->clr = node->clr;
            }
            if (y_original_color == BLACK)
				Delete_Fixup(x);
            delete node;
            return a;
        }
        void PrintTree() const {
            if (empty()) {
                std::cout << "IsEmpty" << std::endl;
                return;
            }
            for(const_iterator it = begin(); it != end(); ++it)
                    std::cout << *it << std::endl;
            std::cout << std::endl;
        }
};

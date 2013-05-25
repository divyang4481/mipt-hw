#pragma once
#include <iostream>
enum EColor{RED, BLACK};

class TMyException
{
        std::string Description;
public:
        TMyException()
        {
                Description = "AAAAAAAAAAAA";
        }
        explicit TMyException(const char* str)
        {
                Description = str;
        }
        const std::string& desc() const
        {
                return Description;
        }
};
template<typename T>
class TTree
{
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
        void destroy(TNode* curr) {
                if (curr != Nil)
                {
                        if (curr -> left != Nil && curr -> left) 
                                destroy (curr -> left);
                        if (curr -> right != Nil && curr -> right)
                                destroy (curr -> right);
                        delete curr;
                }
        }
        void Transplant(TNode* u, TNode* v)
        {
                if (u -> parent == Nil)
                        Root = v;
                else
                {
                        if (u == u -> parent -> left)
                                u -> parent -> left = v;
                        else u -> parent -> right = v;
                }
                if (v != Nil)
                        v -> parent = u -> parent;
        }
        void RightRotate(TNode* x)
        {
                TNode* y = x -> left;
                x -> left = y -> right;
                if (y -> right != Nil)
                        y -> right -> parent = x;
                y -> parent = x -> parent;
                if (x -> parent == Nil)
                        Root = y;
                else {
                        if (x == x -> parent -> right)
                        x -> parent -> right = y;
                        else x -> parent -> left = y;
                }
                y -> right = x;
                x -> parent = y;
        }
        void LeftRotate(TNode* x)
        {
                TNode* y = x -> right;
                x -> right = y -> left;
                if (y -> left != Nil)
                        y -> left -> parent = x;
                y -> parent = x -> parent;
                if (x -> parent == Nil)
                        Root = y;
                else {
                        if (x == x -> parent -> left)
                        x -> parent -> left = y;
                        else x -> parent -> right = y;
                }
                y -> left = x;
                x -> parent = y;                        
        }
        void InsertFixup(TNode* z)
        {
        	while (z -> parent -> color == RED)
        	{
        		if (z -> parent == z -> parent -> parent -> left)
			{
                                TNode* y = z -> parent -> parent -> right;
                                if (y -> color == RED)
                                {
                                        z -> parent -> color = BLACK;
                                        y -> color = BLACK;
                                        z -> parent -> parent -> color = RED;
                                        z = z -> parent -> parent;
                                }
                                else 
                                {
                                        if (z == z -> parent -> right)
                                        {
                                                z = z -> parent;
                                                LeftRotate(z);
                                        }
                                        z -> parent -> color = BLACK;
                                        z -> parent -> parent -> color = RED;
                                        RightRotate(z -> parent -> parent);
                                }
                        }
                        else
                        {
                                TNode* y = z -> parent -> parent -> left;
                                if (y -> color == RED)
                                {
                                        z -> parent -> color = BLACK;
                                        y -> color = BLACK;
                                        z -> parent -> parent -> color = RED;
                                        z = z -> parent -> parent;
                                }
                                else 
                                {
                                        if (z == z -> parent -> left)
                                        {
                                                z = z -> parent;
                                                RightRotate(z);
                                        }
                                        z -> parent -> color = BLACK;
                                        z -> parent -> parent -> color = RED;
                                        LeftRotate(z -> parent -> parent);
                                }
                        }
                }
                Root -> color = BLACK;
        }
        void DeleteFixup(TNode* node)
        {
                while (node != Root && node -> color == BLACK)
                {
                        if (node == node -> parent -> left)
                        {
                                TNode* tmp = node -> parent -> right;
                                if (tmp -> color == RED)
                                {
                                        tmp -> color = BLACK;
                                        node -> parent -> color = RED;
                                        LeftRotate(node -> parent);
                                        tmp = node -> parent -> right;
                                }
                                if (tmp -> left -> color == BLACK && tmp -> right -> color == BLACK)
                                {
                                        tmp -> color = RED;
                                        node = node -> parent;
                                }
                                else
                                {
                                        if (tmp -> right -> color == BLACK)
                                        {
                                                tmp -> left -> color = BLACK;
                                                tmp -> color = RED;
                                                RightRotate(tmp);
                                                tmp = node -> parent -> right;
                                        }
                                        tmp -> color = node -> parent -> color;
                                        node -> parent -> color = BLACK;
                                        tmp -> right -> color = BLACK;
                                        LeftRotate(node -> parent);
                                        node = Root;
                                }
                        }
                        else
                        {
                                TNode* tmp = node -> parent -> left;
                                if (tmp -> color == RED)
                                {
                                        tmp -> color = BLACK;
                                        node -> parent -> color = RED;
                                        RightRotate(node -> parent);
                                        tmp = node -> parent -> left;
                                }
                                
                                if (tmp -> right -> color == BLACK && tmp -> left -> color == BLACK)
                                {
                                        tmp -> color = RED;
                                        node = node -> parent;
                                }
                                else
                                {
                                        if (tmp -> left -> color == BLACK)
                                        {
                                                tmp -> right -> color = BLACK;
                                                tmp -> color = RED;
                                                LeftRotate(tmp);
                                                tmp = node -> parent -> left;
                                        }
                                        tmp -> color = node -> parent -> color;
                                        node -> parent -> color = BLACK;
                                        tmp -> left -> color = BLACK;
                                        RightRotate(node -> parent);
                                        node = Root;
                                }
                        }

                }
                node -> color = BLACK;
        }
//private:
        TNode* Minimum(TNode* node) const
        {
                if (node == Nil)
                        return Nil;
                TNode* curr = node;
                while (curr -> left != Nil)
                        curr = curr -> left;
                return curr;                        
        }
        TNode* Minimum() const
        {
                return Minimum(Root);
        }
        TNode* Maximum(TNode* node) const 
        {
                if (node == Nil)
                        return Nil;
                TNode* curr = node;
                while (curr -> right != Nil)
                        curr = curr -> right;
                return curr;                        
        }
        TNode* Maximum() const
        {
                return Maximum(Root);
        }
public:
        class iterator
        {
                TNode* node;
                TNode* Nil;
        public:
                iterator(TNode* nd, TNode* nil)
                {
                        node = nd;
                        Nil = nil;
                }
                iterator()
                {
                        node = 0;
                        Nil = 0;
                }
                iterator(const iterator& it)
                {
                        node = it.node;
                        Nil = it.Nil;
                }
                iterator& operator++()
                {
                        if (node -> right != Nil)
                        {
                                node = node -> right;
                                while(node -> left != Nil)
                                        node = node -> left;
                                return *this;
                        }
                        for (; node -> parent != Nil; node = node -> parent)
                        {
                                if(node -> parent -> left == node)
                                {
                                        node = node -> parent;
                                        return *this;       
                                }
                        }
                        node = Nil;
                        return *this;
                }
                iterator& operator--()
                {
                        if (node -> left != Nil)
                        {
                                for(;node -> right != Nil; node = node -> right);
                                return *this;
                        }
                        for (;node -> parent != Nil; node = node -> parent)
                        {
                                if(node -> parent -> right == node)
                                {
                                        node = node -> parent;
                                        return *this;
                                }             
                        }
			node = Nil;
                        return *this;
                }
                T& operator*()
                {
                        return node -> key;
                }
                bool operator==(const iterator& it)
                {
                        if (node == it.node)
                                return true;
                        return false;
                }
                bool operator !=(const iterator& it)
                {
                        if (!(*this == it))
                                return true;
                        return false;
                }
                iterator& operator=(const iterator& it)
                {
                        node = it.node;
                        Nil = it.Nil;
                        return *this;
                }
                TNode* nd()
                {
                        return node;
                }
        };
        class const_iterator
        {
                TNode* node;
                TNode* Nil;
        public:
                const_iterator(TNode* nd, TNode* nil)
                {
                        node = nd;
                        Nil = nil;
                }
                const_iterator()
                {
                        node = 0;
                        Nil = 0;
                }
                const_iterator(const const_iterator& it)
                {
                        node = it.node;
                        Nil = it.Nil;
                }
                const_iterator& operator++()
                {
                        if (node -> right != Nil)
                        {
                                node = node -> right;
                                while(node -> left != Nil)
                                        node = node -> left;
                                return *this;
                        }
                        for (; node -> parent != Nil; node = node -> parent)
                        {
                                if(node -> parent -> left == node)
                                {
                                        node = node -> parent;
                                        return *this;       
                                }
                        }
                        node = Nil;
                        return *this;
                }
                const_iterator& operator--()
                {
                        if (node -> left != Nil)
                        {
                                for(;node -> right != Nil; node = node -> right);
                                return *this;
                        }
                        for (;node -> parent != Nil; node = node -> parent)
                        {
                                if(node -> parent -> right == node)
                                {
                                        node = node -> parent;
                                        return *this;
                                }             
                        }
			node = Nil;
                        return *this;
                }
                const T& operator*()
                {
                        return node -> key;
                }
                bool operator==(const const_iterator& it)
                {
                        if (node == it.node)
                                return true;
                        return false;
                }
                bool operator !=(const const_iterator& it)
                {
                        if (!(*this == it))
                                return true;
                        return false;
                }
                const_iterator& operator=(const const_iterator& it)
                {
                        node = it.node;
                        Nil = it.Nil;
                        return *this;
                }
                TNode* nd() const
                {
                        return node;
                }
        };
private:
        void Insert(TNode* node)
        {
                TNode* y = Nil;
                TNode* x = Root;
                while (x != Nil)
                {
                        y = x;
                        if (node -> key < x -> key)
                                x = x -> left;
                        else x = x -> right;
                }
                node -> parent = y;
                if (y == Nil)
                        Root = node;
                else 
                {
                        if (node -> key < y -> key)
                                y -> left = node;
                        else y -> right = node;
                }
                node -> left = Nil;
                node -> right = Nil;
                node -> color = RED;
                InsertFixup(node);
        }
        void Delete(const TNode* pnode)
        {
                if (pnode == Nil)
                        throw TMyException("Error in Delete: pnode == Nil");
                TNode* x;
                TNode* node = const_cast<TNode*> (pnode);
                TNode* y = node;
                EColor yColor = y->color;
                if (node->left == Nil)
                {
                        x = node->right;
                        Transplant(node, node->right);
                }
                else
                {
                        if (node->right == Nil)
                        {
                                x = node -> left;
                                Transplant(node, node -> left);
                        }
                        else
                        {
                                y = const_cast<TNode*>(Minimum(node -> right));
                                yColor = y -> color;
                                x = y -> right;
                                if (y -> parent == node)
                                        x -> parent = y;
                                else
                                {
                                        Transplant(y, y -> right);
                                        y -> right = node -> right;
                                        y -> right -> parent = y;
                                }
                                Transplant(node, y);
                                y -> left = node -> left;
                                y -> left -> parent = y;
                                y -> color = node -> color;
                        }
                        if (yColor == BLACK && x != Nil)
                                DeleteFixup(x);
                }
                delete node;
        }
        TNode* Find (const T& k) const
        {
                TNode* curr = Root;
                while (curr != Nil)
                {
                        if (curr -> key == k)
                                return curr;
                        curr = (k < curr -> key ? curr -> left : curr-> right);
                }
                return Nil;
        }
public:
        TTree() 
        {
                Nil = new TNode;
                Nil -> color = BLACK;
                Root = Nil;
        }
        TTree(const TTree<T>& oth)
        {
                Nil = new TNode;
                Nil -> color = BLACK;
                Root = Nil;
                *this = oth;
        }
        TTree& operator =(const TTree<T>& oth)
        {
                clear();
		for (const_iterator it = oth.begin(); it != oth.end(); ++it)
			insert(*(it));
		return *this;
        }
        ~TTree()
        {
                if (Root != Nil)
                        destroy(Root);
                delete Nil;
        }
        void swap(TTree<T>& oth)
        {
                std::swap(Root, oth.Root);
                std::swap(Nil, oth.Nil);
        }
        iterator begin()
        {

                iterator it(Minimum(), Nil);
                return it;
        }
        iterator end()
        {

                iterator it(Nil, Nil);
                return it;
        }
        const_iterator begin() const
        {

                const_iterator it(Minimum(), Nil);
                return it;
        }
        const_iterator end() const
        {

                const_iterator it(Nil, Nil);
                return it;
        }
        bool empty() const
        {
                return (Root == Nil);
        }
        void clear()
        {
                if (Root != Nil)
                        destroy(Root);
                Root = Nil;
        }
        void erase(iterator it)
        {
                Delete(it.nd());
        }
        iterator find(const T& val)
        {
                TNode* tmp = Find(val);
                iterator it(tmp, Nil);
                return it;
        }
        iterator insert(T val)
        {
                TNode* node = new TNode(val);
                Insert(node);
                iterator it(node, Nil);
                return it;
        }
        void PrintTree() const
        {
                if (empty())
                {
                        std::cout << "IsEmpty" << std::endl;
                        return;
                }
                for(const_iterator it = begin(); it != end(); ++it)
                        std::cout << *it << std::endl;
                std::cout << std::endl;
        }
        
};

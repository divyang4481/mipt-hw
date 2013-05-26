#include <stdlib.h>
#include "rbt.h"
#include <iostream>

using namespace std;

struct TFoo
{
        int Value;
        TFoo() : Value(0) {++Created;}
        TFoo(int val) : Value(val) {++Created;}
        TFoo(const TFoo &other) : Value(other.Value) {++Created;}
        ~TFoo() {++Deleted;}
        static int Created;
        static int Deleted;
        static void PrintStats()
        {
                cout << "TFoo Created: " << Created << endl
                << "TFoo Deleted: "<< Deleted << endl;
        }
        bool operator < (TFoo &other)
        {
                return Value < other.Value;
        }
        bool operator <= (TFoo &other)
        {
                return Value <= other.Value;
        }
        bool operator > (TFoo &other)
        {
                return Value > other.Value;
        }
        TFoo operator = (TFoo oth)
        {
                Value = oth.Value;
                return *this;
        }
};

int TFoo::Created = 0;
int TFoo::Deleted = 0;

/*void PrintNode(const TTree<TFoo>::TNode &node, const TTree<TFoo>::TNode* Nil)
{
        cout << "Node: " << node.key.Value << endl;
        if (node.left != Nil)
                cout << "Left: " << node.left -> key.Value << endl;
        else cout << "Left: Nil" << endl;
        if (node.right != Nil)
                cout << "Right: " << node.right -> key.Value << endl;
        else cout << "Right: Nil" << endl;
        if (node.parent != Nil)
                cout << "Parent: " << node.parent -> key.Value << endl;
        else cout << "Parent: Nil" << endl;
        cout << endl;
}

void PrintTree(const TTree<TFoo>::TNode* node, const TTree<TFoo>::TNode* Nil)
{
        if (node != Nil)
        {
                if (node -> left != 0)
                        PrintTree(node  -> left, Nil);
                PrintNode(*node, Nil);
                if (node -> right != 0)
                        PrintTree(node -> right, Nil);
        }
}
void Test1()
{
        TTree<TFoo> tree;
        for (int i = 0; i < 10; ++i)
        {
                TTree<TFoo>::TNode* node = new TTree<TFoo>::TNode;
                node -> key.Value = rand() % 100;
                tree.Insert(node);
        }
                PrintTree(tree.Root, tree.Nil);
        while (!tree.IsEmpty())
        {
                const TTree<TFoo>::TNode* node = tree.Root;
                PrintNode(*node, tree.Nil);
                tree.Delete(node);
        }
}*/
void Test2()
{
        srand(time(NULL));
        TTree<int> tree;
        for (int i = 0; i < 8; ++i)
                tree.insert(rand() % 100);
        tree.PrintTree();
        TTree<int>::iterator iter = tree.begin();
        ++iter;
        tree.erase(iter);
        tree.PrintTree();
        TTree<int> tree2;
        tree2 = tree;
        tree2.PrintTree();
        tree.clear();
        tree.PrintTree();
        tree.insert(3);
        tree.PrintTree();
        tree.swap(tree2);
        tree.PrintTree();
        tree2.PrintTree();
        iter = tree.find(0);
        if (iter == tree.end())
                cout << "No element" << endl;
        else cout << "Element: " << *iter << endl;
        TTree<TFoo> tree3;
        for (int i = 0; i < 10; ++i)
        {
                TFoo tmp(i);
                tree3.insert(tmp);
        }
}

static void Test3() {
    TTree<TFoo> a;
    for (int i = 0; i < 10; ++i)
        a.insert(TFoo(i));

    TTree<TFoo> b = a;
    for (int i = 0; i < 10; ++i)
        a.insert(TFoo(i));

    TTree<TFoo> c;
    a = c;

    for (TTree<TFoo>::iterator iter = a.begin(); iter != a.end(); ++iter) {
        c.insert(*iter);
    }
}

int main()
{
        try{
            Test3();
        }catch(const std::exception& xcp)
        {
                cout << "ERROR!!!! std::exception: " << xcp.what() << endl;
        }
        catch(const TMyException& xcp)
        {
                cout << "ERROR!!!! TMyException: " << xcp.desc() << endl;
        }
        catch(...)
        {
                cout << "Undefined exception" << endl;
        }
		TFoo::PrintStats();
        return 0;
}

#include <stdlib.h>
#include "rbt.h"
#include <iostream>
#include <stdio.h>      
#include <time.h> 
using namespace std;

struct TFoo {
        int Value;
        TFoo() : Value(0) {++Created;}
        TFoo(int val) : Value(val) {++Created;}
        TFoo(const TFoo &other) : Value(other.Value) {++Created;}
        ~TFoo() {++Deleted;}
        static int Created;
        static int Deleted;
        static void PrintStats() {
			cout << "TFoo Created: " << Created << endl
			<< "TFoo Deleted: "<< Deleted << endl;
        }
        bool operator < (TFoo &other) {
			return Value < other.Value;
        }
        bool operator <= (TFoo &other) {
			return Value <= other.Value;
        }
        bool operator > (TFoo &other) {
			return Value > other.Value;
        }
        TFoo& operator = (const TFoo &oth) {
			Value = oth.Value;
			return *this;
        }

        bool operator==(const TFoo& other) {
            return Value == other.Value;
        }
};

int TFoo::Created = 0;
int TFoo::Deleted = 0;

void Test2() {
    srand(time(NULL));
    TRBTree<int> tree;
    for (int i = 0; i < 8; ++i)
        tree.insert(rand() % 100);
    tree.PrintTree();
    TRBTree<int>::iterator iter = tree.begin();
    ++iter;
    tree.erase(iter);
    tree.PrintTree();
    TRBTree<int> tree2;
    tree2 = tree;
    tree2.PrintTree();
    tree.clear();
    tree.PrintTree();
    tree.insert(10);
    tree.PrintTree();
    tree.swap(tree2);
    tree.PrintTree();
    tree2.PrintTree();
    iter = tree.find(0);
    if (iter == tree.end())
            cout << "no any elements" << endl;
    else cout << "emelents: " << *iter << endl;

}

static void Test3() {
    typedef TRBTree<TFoo> TTreeFoo;

    TTreeFoo a;
    for (int i = 0; i < 100; ++i)
        a.insert(TFoo(i));

    TTreeFoo b = a;
    //for (int i = 0; i < 100; ++i)
    //    b.insert(TFoo(i));

    //a.swap(b);

    //for (TTreeFoo::iterator iter = a.begin(); iter != a.end(); ++iter)
    //    cout << *iter << endl;
}

int main() {
	Test3();
	return 0;
}

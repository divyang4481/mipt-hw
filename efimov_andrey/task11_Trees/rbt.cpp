#include <stdlib.h>
#include "rbt.h"
#include <iostream>
#include <time.h>

using namespace std;

struct Tester{
	int Value;
	Tester(): Value(0) {++Created;}
	Tester(int val): Value(val) {++Created;}
	Tester(const Tester &other): Value(other.Value) {++Created;}
	~Tester() {++Deleted;}
	static int Created;
	static int Deleted;
	static void Stats(){
		cout << "Testers Created: " << Created << endl
			<< "Testers Deleted: "<< Deleted << endl;
		cout << ((Created-Deleted==0)?"All clear":"Close something") << endl;
	}
	bool operator< (Tester &other){
		return Value < other.Value;
	}
	bool operator<= (Tester &other){
		return Value <= other.Value;
	}
	bool operator> (Tester &other){
		return Value > other.Value;
	}
	Tester operator = (Tester other){
		Value = other.Value;
		return *this;
	}
};

int Tester::Created = 0;
int Tester::Deleted = 0;

void PrintNode(const TTree<Tester>::TNode &node, const TTree<Tester>::TNode* Nil){
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

void PrintTree(const TTree<Tester>::TNode* node, const TTree<Tester>::TNode* Nil)
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


void ATestlessInnuendo(){
	srand(time(NULL));
	TTree<int> A;
	for (int i=0; i<12; ++i)
		A.insert(rand()%100);
	cout << "Checking insertions: " << endl << "A: ";
	A.PrintTree();
	TTree<int> B;
	B = A;
	cout << "Checking Operator = : " << endl << "A: ";
	A.PrintTree();
	cout << "B: ";
	B.PrintTree();
	TTree<int>::iterator iter = A.begin();
	iter++; iter++;
	A.erase(iter);
	cout << "Checking \'Erase\' -- Erasing no. 3." << endl << "A :";
	A.PrintTree();
	cout << "B: ";
	B.PrintTree();

	A.swap(B);
	cout << "Checking Swap:" << endl << "A: ";
	A.PrintTree();
	cout << "B: ";
	B.PrintTree();

	A.clear();
	cout << "Checking Clear:" << endl << "A: ";
	A.PrintTree();
	for (int i=0; i<12; ++i)
		A.insert(rand()%100);
	cout << "Inserted back some stuff:" << endl << "A: ";
	A.PrintTree();
	iter = A.find(42);
	cout << "Checking Find -- if 42 is one of the elements, should give it, otherwise say so" << endl;
	if (iter == A.end())
		cout << "No element" << endl;
	else cout << "Element: " << *iter << endl;
	system("pause");
}

void ATestfulObservation(){
	{
		TTree<Tester> A;
		int N=rand()%10+10;
		for (int i = 0; i < N; ++i)
			A.insert(Tester(i));
		TTree<Tester> B = A;
		for (int i = 0; i < N; ++i)
			A.insert(Tester(i));
		TTree<Tester> C;
		A = C;
		for (TTree<Tester>::iterator iter = A.begin(); iter != A.end(); ++iter) {
			C.insert(*iter);
		}
	}
	Tester::Stats();
	system("pause");
}

int main(){
	ATestlessInnuendo();
	ATestfulObservation();
	return 0;
}
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <crtdbg.h>

using namespace std;

class TNode
{
public: 
	int value;
	TNode* prev;
	TNode* next;
};

class TList
{
public:
	TList(){ // ����������� �� ��������� - ������� ������ ������
		size = 0;
		first = NULL;
		last = NULL;
	}
	TList(const TList& other) { // ����������� �����������
		size = 0;
		first = NULL;
		last = NULL;
		const TNode* node = other.FirstNode();
		while (node != NULL) {
			PushBack(node->value);
			node = node->next;
		}
		

	}

	TList& operator=(const TList &other){ // �������� ����������� ������������
	
	
	}
	~TList() { // ���������� (������� ��� ��������, �������� ������� ������)
		Delete(first, last);
	}
	bool IsEmpty() const{ // ���������� true, ���� ������ ������
		return (first == NULL);
	}
	int First(){ // ���������� ������ �� ������ ������� ������ 
	// (���� ������ ������ - undefined behaviour)
		if (first != NULL)
			return first->value;
		else
		{}
	}

	int Last(){ // ���������� ������ �� ��������� ������� ������
	//(���� ������ ������ - undefined behaviour)
		if (last != NULL)
			return last->value;
		else
		{}	
	
	}
	TNode* FirstNode() { // ���������� ��������� �� ��������� ���� ������
		return first;
	
	}

	const TNode* FirstNode() const { // ���������� ��������� �� ��������� ���� ������
		return first;
	
	}

	TNode* LastNode() { // ���������� ��������� �� �������� ���� ������
		return last;
	}


	const TNode* LastNode() const { // ���������� ��������� �� �������� ���� ������
		return last;
	}

	void PushBack(int val){// ��������� � ����� ������ ������� �� ��������� val
		TNode* node = new TNode;
		node->value = val;
		node->next = NULL;
		node->prev = last;
		if (last == NULL)
			first = node;
		else
			last->next = node;
		last = node;
		size++;
		
	}
	void PushBack(TNode* node) { // ��������� � ����� ������ ���� node.
	// ���� ��� ���� ��������� �� �������� �������-������
		node->next = NULL;
		node->prev = last;
		if (last == NULL)
			first = node;
		else
			last->next = node;
		last = node;
		size++;
	}
	void PushFront(int val) // ��������� � ������ ���c�� ������� �� ��������� val
	{
		TNode* node = new TNode;
		node->value = val;
		node->next = first;
		node->prev = NULL;

		if (first == NULL) 
			last = node;
		else 
			first->prev = node;
		first = node;
		size++;

	}
	void PushFront(TNode* node){ // ��������� � ������ ������ ���� node.
	// ���� ��� ���� ��������� �� �������� �������-������
		node->next = first;
		node->prev = NULL;

		if (first == NULL) 
			last = node;
		else 
			first->prev = node;
		first = node;
		size++;

	}
	void Insert(TNode* where, int val); // ��������� ����� ����� where ���� �� ��������� val

	void Insert(TNode* where, TNode* node); // ��������� ����� ����� where ���� node.
	// ���� ��� ���� ��������� �� �������� �������-������

	void Insert(TNode* where, TList &other); // ��������� ����� ����� where ��� �������� ������ other (�� O(1)).
	// ��� ���� ������ other ���������� ������ � ��� ��� �������� ��������� �� ��������
	// �������� �������-������ (��� ����� ������)

	int PopLast() { // ��������� �� ������ ��������� ��������, ����������� ������,
	// ���������� ��� ����, � ���������� �������� ��������
		TNode* node = LastNode(); 
		TNode* n;
		n->value = node->value;
		n->next = node->next;
		n->prev = node->prev;
		Delete(node);
		return(n->value);
	}
	int PopFirst(); // ��������� �� ������ ������ �������, ����������� ������,
	// ���������� ��� ����, � ���������� �������� ��������

	TNode* ExtractLast() { // ��������� �� ������ ��������� ���� � ���������� ��������� �� ����;
	// �� �������� ���� �������� ��������� ����� ���������� ���
	
	
	}
	TNode* ExtractFirst(); // ��������� �� ������ ������ ���� � ���������� ��������� �� ����;
	// �� �������� ���� �������� ��������� ����� ���������� ���

	void Delete(TNode* node) {// ������� �� ������ ���� node
		if (first == last)
		{ first = NULL;
			last = NULL;
		}
		else if (node == first) {
			(node->next)->prev = NULL;
			first = node->next;
		}
		else if (node == last) {
			(node->prev)->next = NULL;
			last = node->prev;
		}
		else {		
			(node->next)->prev = node->prev;
			(node->prev)->next = node->next;
		}
		delete node;
		size--;
		}

	void Delete(TNode* from, TNode *to) { // ������� �� ������ ��� �������� �� from �� to
		TNode* node = from;
		while (node != to) {
			node = node->next;
			Delete(node->prev);
		}	
		Delete(to);
	}

	TNode* Extract(TNode* node); // ��������� �� ������ ���� node � ���������� ��������� �� ����;
	// �� �������� ���� �������� ��������� ����� ���������� ���

	TList Extract(TNode* from, TNode* to); // ��������� �� ������ �������� �������� �� from �� to.
	// ���������� ������ TList, ���������� ���� ��������
private:
	int size;
	TNode* first;
	TNode* last;
};

int main()
{
	{
		TList List1;
		int n, a;
		cin >> n;
		for(int i = 0; i< n; i++) {
			cin >> a;
			List1.PushFront(a);
		}
		TList List2(List1);
		List2.PushBack(5);
	}
	
	//List2.Delete(List2.FirstNode()->next, List2.LastNode()->prev);
	//_CrtDumpMemoryLeaks();
	return 0;
}
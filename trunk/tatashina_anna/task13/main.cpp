#include <iostream>
#include <cstdio>
#include <cstdlib>
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
		TNode* node = other.FirstNode();
		while (node != NULL) {
			PushBack(node->value);
			node = node->next;
		}
		

	}

	TList& operator=(const TList &other); // �������� ����������� ������������

	//~TList(); // ���������� (������� ��� ��������, �������� ������� ������)

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
	TNode* LastNode() { // ���������� ��������� �� �������� ���� ������
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
	void PushFront(int val) // ��������� � ������ ����� ������� �� ��������� val
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

	int PopLast(); // ��������� �� ������ ��������� ��������, ����������� ������,
	// ���������� ��� ����, � ���������� �������� ��������

	int PopFirst(); // ��������� �� ������ ������ �������, ����������� ������,
	// ���������� ��� ����, � ���������� �������� ��������

	TNode* ExtractLast(); // ��������� �� ������ ��������� ���� � ���������� ��������� �� ����;
	// �� �������� ���� �������� ��������� ����� ���������� ���

	TNode* ExtractFirst(); // ��������� �� ������ ������ ���� � ���������� ��������� �� ����;
	// �� �������� ���� �������� ��������� ����� ���������� ���

	void Delete(TNode* node); // ������� �� ������ ���� node

	void Delete(TNode* from, TNode *to); // ������� �� ������ ��� �������� �� from �� to

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
	TList List;
	int n, a;
	cin >> n;
	for(int i = 0; i< n; i++) {
		cin >> a;
		List.PushBack(a);
	}
    return 0;
}
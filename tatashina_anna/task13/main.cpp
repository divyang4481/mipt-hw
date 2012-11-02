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
	TList(){ // конструктор по умолчанию - создает пустой список
		size = 0;
		first = NULL;
		last = NULL;
	}
	TList(const TList& other) { // конструктор копирования
		size = 0;
		first = NULL;
		last = NULL;
		TNode* node = other.FirstNode();
		while (node != NULL) {
			PushBack(node->value);
			node = node->next;
		}
		

	}

	TList& operator=(const TList &other); // оператор копирующего присваивания

	//~TList(); // деструктор (удаляет все элементы, которыми владеет список)

	bool IsEmpty() const{ // возвращает true, если список пустой
		return (first == NULL);
	}
	int First(){ // возвращает ссылку на первый элемент списка 
	// (если список пустой - undefined behaviour)
		if (first != NULL)
			return first->value;
		else
		{}
	}

	int Last(){ // возвращает ссылку на последний элемент списка
	//(если список пустой - undefined behaviour)
		if (last != NULL)
			return last->value;
		else
		{}	
	
	}
	TNode* FirstNode() { // возвращает указатель на начальную ноду списка
		return first;
	
	}
	TNode* LastNode() { // возвращает указатель на конечную ноду списка
		return last;
	}
	void PushBack(int val){// вставляет в конец списка элемент со значением val
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
	void PushBack(TNode* node) { // вставляет в конец списка узел node.
	// Узел при этом переходит во владение объекта-списка
		node->next = NULL;
		node->prev = last;
		if (last == NULL)
			first = node;
		else
			last->next = node;
		last = node;
		size++;
	}
	void PushFront(int val) // вставляет в начало спика элемент со значением val
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
	void PushFront(TNode* node){ // вставляет в начало списка узел node.
	// Узел при этом переходит во владение объекта-списка
		node->next = first;
		node->prev = NULL;

		if (first == NULL) 
			last = node;
		else 
			first->prev = node;
		first = node;
		size++;

	}
	void Insert(TNode* where, int val); // вставляет перед узлом where узел со значением val

	void Insert(TNode* where, TNode* node); // вставляет перед узлом where узел node.
	// Узел при этом переходит во владение объекта-списка

	void Insert(TNode* where, TList &other); // вставляет перед узлом where все элементы списка other (за O(1)).
	// При этом список other становится пустым и все его элементы переходят во владение
	// текущего объекта-списка (чей метод вызван)

	int PopLast(); // извлекает из списка последний элемента, освобождает память,
	// выделенную под него, и возвращает значение элемента

	int PopFirst(); // извлекает из списка первый элемент, освобождает память,
	// выделенную под него, и возвращает значение элемента

	TNode* ExtractLast(); // извлекает из списка последний узел и возвращает указатель на него;
	// за владение узла отвечает вызвавший метод клиентский код

	TNode* ExtractFirst(); // извлекает из списка первый узел и возвращает указатель на него;
	// за владение узла отвечает вызвавший метод клиентский код

	void Delete(TNode* node); // удаляет из списка узел node

	void Delete(TNode* from, TNode *to); // удаляет из списка все элемента от from до to

	TNode* Extract(TNode* node); // извлекает из списка узел node и возвращает указатель на него;
	// за владение узла отвечает вызвавший метод клиентский код

	TList Extract(TNode* from, TNode* to); // извлекает из списка интервал элментов от from до to.
	// возвращает объект TList, содержащий этот интервал
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
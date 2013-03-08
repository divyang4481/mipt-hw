#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <crtdbg.h>

using namespace std;

class TNode {
public: 
	int value;
	TNode* prev;
	TNode* next;
};

class TList {
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
		const TNode* node = other.FirstNode();
		while (node != NULL) {
			PushBack(node->value);
			node = node->next;
		}
	}

	TList& operator=(const TList &other){ // оператор копирующего присваивания
		Delete(first, last);
		const TNode* node = other.FirstNode();
		while (node != NULL) {
			PushBack(node->value);
			node = node->next;
		}
	
	}
	~TList() { // деструктор (удаляет все элементы, которыми владеет список)
		Delete(first, last);
	}

	bool IsEmpty() const{ // возвращает true, если список пустой
		return (first == NULL);
	}

	int First(){ // возвращает ссылку на первый элемент списка 
	// (если список пустой - undefined behaviour)
		if (first != NULL)
			return first->value;
	}
	int Last(){ // возвращает ссылку на последний элемент списка
	//(если список пустой - undefined behaviour)
		if (last != NULL)
			return last->value;
	}

	TNode* FirstNode() { // возвращает указатель на начальную ноду списка
		return first;
	
	}
	const TNode* FirstNode() const { // возвращает указатель на начальную ноду списка
		return first;
	
	}
	
	TNode* LastNode() { // возвращает указатель на конечную ноду списка
		return last;
	}
	const TNode* LastNode() const { // возвращает указатель на конечную ноду списка
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
	void PushFront(int val) // вставляет в начало спиcка элемент со значением val
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
	
	void Insert(TNode* where, int val){ // вставляет перед узлом where узел со значением val
		TNode* node = new TNode();
		node->value = val;
		Insert(where, node);
	}
	void Insert(TNode* where, TNode* node) { // вставляет перед узлом where узел node.
	// Узел при этом переходит во владение объекта-списка
		TNode* temp = where->prev;
		node->next = where;
		where->prev = node;
		node->prev = temp;
		if(temp)
			temp->next = node;
	}
	void Insert(TNode* where, TList &other) { // вставляет перед узлом where все элементы списка other (за O(1)).
	// При этом список other становится пустым и все его элементы переходят во владение
	// текущего объекта-списка (чей метод вызван)
		TNode* temp = where->prev;
		TNode* last = other.LastNode();
		TNode* first = other.FirstNode();
		last->next = where;
		where->prev = last;
		first->prev = temp;
		if(temp)
			temp->next = first;
		other.Delete(first, last);
	}
	int PopLast() { // извлекает из списка последний элемента, освобождает память,
	// выделенную под него, и возвращает значение элемента
		TNode* node = LastNode(); 
		int n = LastNode()->value;
		Delete(node);
		return(n);
	}
	int PopFirst() { // извлекает из списка первый элемент, освобождает память,
		TNode* node = FirstNode(); 
		int n = FirstNode()->value;
		Delete(node);
		return(n);
	}// выделенную под него, и возвращает значение элемента

	TNode* ExtractLast() { // извлекает из списка последний узел и возвращает указатель на него;
	// за владение узла отвечает вызвавший метод клиентский код
		TNode* node = LastNode(); 
		TNode* n;
		n->value = node->value;
		n->next = node->next;
		n->prev = node->prev;
		Delete(node);
		return(n);
	
	}
	TNode* ExtractFirst() { // извлекает из списка первый узел и возвращает указатель на него;
	// за владение узла отвечает вызвавший метод клиентский код
		TNode* node = FirstNode(); 
		TNode* n;
		n->value = node->value;
		n->next = node->next;
		n->prev = node->prev;
		Delete(node);
		return n;
	
	}
	void Delete(TNode* node) {// удаляет из списка узел node
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

	void Delete(TNode* from, TNode *to) { // удаляет из списка все элемента от from до to
		TNode* node = from;
		while (node != to) {
			node = node->next;
			Delete(node->prev);
		}	
		Delete(to);
	}

	TNode* Extract(TNode* node) // извлекает из списка узел node и возвращает указатель на него;
	// за владение узла отвечает вызвавший метод клиентский код
	{
		TNode* n;
		n->value = node->value;
		n->next = node->next;
		n->prev = node->prev;
		Delete(node);
		return n;
	}
	TList Extract(TNode* from, TNode* to)   // извлекает из списка интервал элементов от from до to.
											 // возвращает объект TList, содержащий этот интервал
	{
		TList result;
		for(TNode* i = from; i != to->next; i = i->next)
		{
			result.PushBack(i);
		}
		from->prev->next = to->next;
		to->next->prev = from->prev;
		return result;
	};

    void Print() {
        for (TNode *i = first; i != 0; i = i->next)
            cout << i->value << ' ';
        cout << endl;
    };
private:
	int size;
	TNode* first;
	TNode* last;
};

int main()
{
	
		TList List1;
		int n, a, b;
		cin >> n;
		for(int i = 0; i < n; i++) {
			cin >> a;
			List1.PushBack(a);
		}
		if (List1.IsEmpty() == false)
			List1.Print();
		
		cout << "First element = " << List1.First() << endl;
		cout << "Last element = " << List1.Last() << endl;
		cout << "Push Front: " << endl;
			cin >> a;
			List1.PushFront(a);
		cout << "Push Back: " << endl;
			cin >> a;
			List1.PushBack(a);
		
		List1.Print();

		cout << "What element I can insert before last?" << endl;
			cin >> b;

		List1.Insert(List1.LastNode(), b);
		List1.Print();	
		
		cout << "Delete first element!" << endl;
		List1.Delete(List1.FirstNode());
		List1.Print();

		cout << "Razdelim na 2 spiska" << endl;
		TNode* i = (List1.FirstNode()) -> next;
		TNode* j = (List1.LastNode()) -> prev;
		TList List2 = List1.Extract(i,j);
		List1.Print();
		List2.Print();




		cin >> n;
	//List2.Delete(List2.FirstNode()->next, List2.LastNode()->prev);
	//_CrtDumpMemoryLeaks();
	return 0;
}
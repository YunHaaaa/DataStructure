////////////////////////////////////////////////////////////////////////
// HW3:Doubly Linked List (DLL)
// Name: Yun Ha Eun
// ID: 20203110
// Description :
//   Test function that use Doubly Linked List
// Functions :
//   Insert - node�� current�� ��, �� / list�� �� ��, �� �ڿ� ����
//   DeleteCurrent - current node�� ����
//   LocateCurrent - ���ϴ� ��ġ�� �Է¹޾� current�� ����, �ش� ������ ���
//   UpdateCurrent - current�� ��ġ�� �������� �� ��ü
//   DisplayList - Printout the list
//   isEmpty - ����Ʈ�� ������� Ȯ��
// Variables :
//   Pointer head - ����Ʈ�� ù��° ���
//   Pointer current - ������ġ ���
//   Pointer next - Node�� ����, ���� node�� ��Ÿ���� ��ũ
//   Pointer prev - Node�� ����, ���� node�� ��Ÿ���� ��ũ
//	 size - ����Ʈ�� ����
/////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

template <class Type> class List;

template <class Type>
class Node {
	friend class List<Type>;
private:
	Type val{};
	Node<Type>* next;
	Node<Type>* prev;
	Node(Type data) { val = data; next = 0; prev = 0; }
};


template <class Type>
class List {

private:
	Node<Type>* head; // ����Ʈ�� ù��° ���
	Node<Type>* current; // ������ġ ���
	int size = 0;
	// �޴��� ��� action ���Ŀ��� �ش� ��尡 current position�� ��
public:
	List();
	~List();
	
	void insertAfter(Type);
	void insertBefore(Type);
	void insertFirst(Type);
	void insertLast(Type);
	
	void deleteCurrent();
	void locateCurrent(int);
	void updateCurrent(Type);
	
	int isEmpty() { return (head == 0); } // ���� ����Ʈ�� ������� ���θ� �˻�

	void displayList(int); // ���� ����Ʈ�� �� ������ ����ϴ� �Լ�
};

////////////////////////////////////////////////////////////////
// function : insertAfter
// - insert�� �����͸� �Է¹޴´�
// - data�� ������ ���ο� ��� ����
// - current node�ڿ� insert
// - insert�� ��带 current node�� ����
////////////////////////////////////////////////////////////////

template <class Type>
void List<Type>::insertAfter(Type data) {
	Node<Type>* temp = new Node<Type>(data);
	if (isEmpty()) {
		head = temp;
		temp->next = 0;
	}
	else if (current->next != NULL) {
		// insert in the middle
		temp->prev = current;
		temp->next = current->next;
		current->next->prev = temp;
		current->next = temp;
	}
	else {
		// insert in the last
		insertLast(data);
	}
	current = temp;
	size++;
}

////////////////////////////////////////////////////////////////
// function : insertBefore
// - insert�� �����͸� �Է¹޴´�
// - data�� ������ ���ο� ��� ����
// - current node�տ� insert
// - insert�� ��带 current node�� ����
////////////////////////////////////////////////////////////////

template <class Type>
void List<Type>::insertBefore(Type data) {
	Node<Type>* temp = new Node<Type>(data);
	Node<Type>* p, * q;
	if (isEmpty())
		head = temp;
	else if (current = head)
		// insert in the front & head �̵� = head node �տ� insert
		insertFirst(data);
	else {
		// insert in the middle & last  = �̵� �� insert
		p = head;
		q = head;
		while ((p != 0) && (p->val < temp->val)) {
			p = q;
			p = p->next;
		}
		temp->next = p;
		temp->prev = q;
		p->prev = temp;
		q->next = temp;
	}
	size++;
}

////////////////////////////////////////////////////////////////
// function : insertFirst
// - insert�� �����͸� �Է¹޴´�
// - data�� ������ ���ο� ��� ����
// - list�� �� �տ� ��� ��ġ, head �̵�
// - insert�� ��带 current node�� ����
////////////////////////////////////////////////////////////////

template <class Type>
void List<Type>::insertFirst(Type data) {
	Node<Type>* temp = new Node<Type>(data);
	if (isEmpty())
		head = temp;
	else {
		// head node ������ temp node insert
		temp->next = head;
		head->prev = temp;
		head = temp;
	}
	current = temp;
	size++;
}

////////////////////////////////////////////////////////////////
// function : insertLast
// - insert�� �����͸� �Է¹޴´�
// - data�� ������ ���ο� ��� ����
// - list�� ���� �������� ��� ��ġ
// - insert�� ��带 current node�� ����
////////////////////////////////////////////////////////////////

template <class Type>
void List<Type>::insertLast(Type data) {
	Node<Type>* p, * q;
	Node<Type>* temp = new Node<Type>(data);
	if (isEmpty())
		head = temp;
	else {
		//find last node & insert - p = head, while ������ p �̵�
		p = head;
		q = head;
		while (p != 0) {
			q = p;
			p = p->next;
		}
		temp->next = p;
		temp->prev = q;
		//p->prev = temp;
		q->next = temp;
	}
	current = temp;
	size++;
}

////////////////////////////////////////////////////////////////
// function : deleteCurrent
// - current node ����
// - ������ ����� �ٷ� ���̳� ���� node�� current node�� ����
////////////////////////////////////////////////////////////////

template <class Type>
void List<Type>::deleteCurrent() {
	Node<Type>* p;
	if (isEmpty())
		cout << "List Empty";
	else if (current == head) {
		// head node ����, head �̵�
		p = current;
		head = head->next;
		delete(p);
	}
	else if (current->next != NULL) {
		current->prev->next = current->next;
		current->next->prev = current->prev;
		p = current;
		current = current->next;
		delete(p);
	}
	else {
		// ������ ��� ����
		current->prev->next = 0;
		p = current;
		current = current->prev;
		delete(p);
	}
	size--;
}

////////////////////////////////////////////////////////////////
// function : locateCurrent
// - �̵��� ��ġ�� �Է¹޴´�
// - �ش� ��ġ�� �ִ� data���
// - �ش� node�� current node�� ����
////////////////////////////////////////////////////////////////

template <class Type>
void List<Type>::locateCurrent(int nTH) { 
	Node<Type>* p, * q;
	if (isEmpty())
		cout << "List Empty\n";
	else if (size >= nTH) {
		// p = head & find location
		p = head;
		q = head;
		for (int i = 0; i < nTH - 1; i++) {
			q = p;
			p = p->next;
		}
		current = p;
		//print current-value
		cout << nTH << " * " << p->val << endl;
	}
	else
		cout << "No such a line\n";
}

////////////////////////////////////////////////////////////////
// function : updateCurrent
// - insert�� �����͸� �Է¹޴´�
// - ���� current�� ��ġ�� �������� ���� �Է¹��� ������ ��ü
////////////////////////////////////////////////////////////////

template <class Type>
void List<Type>::updateCurrent(Type newdata) {
	current->val = newdata;
}

////////////////////////////////////////////////////////////////
// function : displayList
// - ��ü ����Ʈ ���
////////////////////////////////////////////////////////////////

template <class Type>
void List<Type>::displayList(int nTH) {
	Node<Type>* p;
	if (isEmpty())
		cout << "List is empty!\n" << endl;
	else if (nTH == 0) {
		p = head;
		cout << "--- List ---\n";
		for (int i = 1; p != 0; i++) {
			cout << setw(5) << i << " : " << p->val << endl;
			p = p->next;
		}
	}
	else {
		p = head;
		cout << "--- List ---\n";
		for (int i = 1; p != 0; i++) {
			if (i == nTH)
				cout << setw(5) << i << " * " << p->val << endl;
			else
				cout << setw(5) << i << " : " << p->val << endl;
			p = p->next;
		}
	}
}

template <class Type>
List<Type>::List() {}

template <class Type>
List<Type>::~List() {
	Node<Type>* p;

	while (head != 0) {
		p = head;
		head = head->next;
		delete p;
	}
}


int main(void) {
	List<int> list;
	int a;
	int data = 1;
	int nTH = 0;
	while (true) {
		cout << "(1) insertAfter (2) insertBefore (3) insertFirst (4) insertLast (5) deleteCurrent (6) locateCurrent (7) updateCurrent (8) displayList (9) Quit => ";
		cin >> a;
		// /*
		switch (a) {
		case 9:
			list.~List();
			exit(1);
		case 8:
			break;
		case 7:
			cout << "Enter a number => ";
			cin >> data;
			list.updateCurrent(data);
			break;
		case 6:
			int pos;
			cout << "Enter a poition to locate => ";
			cin >> pos;
			nTH = pos;
			list.locateCurrent(pos);
			break;
		case 5:
			list.deleteCurrent();
			break;
		case 4:
			cout << "Enter a number => ";
			cin >> data;
			list.insertLast(data);
			break;
		case 3:
			cout << "Enter a number => ";
			cin >> data;
			list.insertFirst(data);
			break;
		case 2:
			cout << "Enter a number => ";
			cin >> data;
			list.insertBefore(data);
			break;
		case 1:
			cout << "Enter a number => ";
			cin >> data;
			list.insertAfter(data);
			break;
		}
		list.displayList(nTH);
	}
	return 0;
}

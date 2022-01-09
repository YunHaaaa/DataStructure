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
	int data;
	char name[10];
	Node<Type>* next;
	Node<Type>* prev;
	Node(int val, char str[]) { data = val; strcpy_s(name, str); next = 0; prev = 0; }

	//friend class List<Type>;
};


template <class Type>
class List {

private:
	Node<Type>* head; // ����Ʈ�� ù��° ���
	Node<Type>* current; // ������ġ ���
	// �޴��� ��� action ���Ŀ��� �ش� ��尡 current position�� ��
public:
	List();
	~List();
	/*
	void insertAfter(Type);
	void insertBefore(Type);
	void insertFirst(Type);
	void insertLast(Type);
	*/
	int isEmpty() { return (head == 0); } // ���� ����Ʈ�� ������� ���θ� �˻�
	void insertList(int, char[]);// int, char[]); // ���� ����Ʈ�� ��带 �����ϴ� �Լ�
	void deleteList(int); // ���� ����Ʈ�� ��带 �����ϴ� �Լ�
	void forwardList(); // ���� ����Ʈ�� ������ ������ head���� ���
	void backwardList(); // ���� ����Ʈ�� ������ ������ �������� ���
	void searchList(int); // ���� ����Ʈ���� �����͸� ã�� �Լ�
	void displayList(); // ���� ����Ʈ�� �� ������ ����ϴ� �Լ�
};

template <class Type>
List<Type>::List(){}

template <class Type>
void List<Type>::insertList(int data, char name[]) {
	Node<Type>* temp = new Node<Type>(data, name);
	Node<Type>* p, * q;

	if (head == 0)
		head = temp;
	else if (temp->data < head->data) { // head node �տ� ����
		temp->next = head;
		head->prev = temp;
		head = temp;
	}
	else {
		p = head;
		q = head;
		while ((p != 0) && (p->data < temp->data)) { // �̵� - �� ��ġ ã��
			q = p;
			p = p->next;
		}
		if (p != 0) { // �߰��� ����
			temp->next = p;
			temp->prev = q;
			q->next = temp;
			p->prev = temp;
		}
		else { // temp�� ���� ū��� = ������ ��忡 ���� �� ���
			q->next = temp;
			temp->prev = q;
		}
	}
}

template <class Type>
void List<Type>::deleteList(int key) {
	Node<Type>* p, * q;
	if (head->data == key) { // ������ ��尡 head �� ���
		p = head;
		head = head->next;
		head->prev = 0;
		delete p;
	}
	else { // ��� ��尡 ������ ���
		q = head;
		p = head;
		while (p != 0 && p->data != key) { // �ڸ� ã�� �� ���� �̵�
			q = p;
			p = p->next;
		}
		if (p != 0) {
			q->next = p->next;
			if (p->next != 0)
				p->next->prev = q;
			delete p;
		}
		else
			cout << key << " is not in the list\n";
	}
}

template <class Type>
void List<Type>::forwardList() { // ���������� ���
	if (!isEmpty()) {
		Node<Type>* p = head;
		cout << "----- Forward List -----\n";
		while (p != 0) {
			cout << p->data << " " << p->name << endl;
			p = p->next;
		}
	}
	else
		cout << "List is empty!\n";
}

template <class Type>
void List<Type>::backwardList() {
	if (!isEmpty()) {
		Node<Type>* p = head;
		while (p->next != 0)
			p = p->next;
		cout << "----- Backward List -----\n";
		while (p != 0) {
			cout << p->data << " " << p->name << endl;
			p = p->prev;
		}
	}
	else
		cout << "List is empty!\n";
}

template <class Type>
void List<Type>::searchList(int key) {
	if (!isEmpty()) {
		Node<Type>* p = head;
		while (p != 0 && p->data != key)
			p = p->next;
		if (p != 0)
			cout << p->data << " is in the list\n";
		else
			cout << key << " is not in the list\n";
	}
	else
		cout << "List is empty!\n";
}

template <class Type>
void List<Type>::displayList() {
	Node<Type>* p;
	if (head == 0) cout << "List is empty!" << endl;
	else {
		p = head;
		cout << "--- List ---\n";
		for (int i = 1; p != 0; i++) {
			cout << setw(5) << i << " : " << p->data << endl;
			p = p->next;
		}
	}
}

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
	while (true) {
		cout << "1. insert 2. delete 3. search 4. forward 5. backward 6. Quit => ";
		cin >> a;
	// /*
		switch (a) {
		case 6:
			list.~List();
			exit(1);
		case 5:
			list.backwardList();
			break;
		case 4:
			list.forwardList();
			break;
		case 3:
			cout << "Enter a number => ";
			cin >> data;
			list.searchList(data);
			break;
		case 2:
			cout << "Enter a number => ";
			cin >> data;
			list.deleteList(data);
			break;
		case 1:
			char n[10];
			cout << "Enter a number => ";
			cin >> data;
			cout << "Enter a name => ";
			cin >> n;
			list.insertList(data, n);
			break;
		}
		list.displayList(); // */
	}
	return 0;
}

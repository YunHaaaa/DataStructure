#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* next;
};

class ChainList {
private:
	Node* head;

public:
	ChainList() { head = 0; }
	void insert(int);
	void append(int);
	bool isEmpty();
	void display();
};

class Node {
private:
	int data;
	Node* next;
	friend class List;
};

int main() {
	// Node ����
	// �� �տ� �����ϱ� (list�� empty�� ���)
	Node* temp = new Node;
	temp->data = num;
	temp->next - 0;
	head = temp;

	// (head node�� 0�� �ƴ� ���)
	temp->next = head;
	head = temp;

	// head node �ڿ� node ������ ��� 
	if (head->next = 0)
		head->next = temp;
	else
	{
		temp->next = head->next;
		head->next = temp;
	}

	// �� �ڿ� node�� ���� ���
	Node* temp = new Node;
	temp->data = num;
	temp->next = 0;

	if head == 0
		head = temp;
	else {
		p = head;
		while (p->next != 0)
			p = p->next;
		p->next = temp;
	}

	// ����ϱ�
	p = head;
	while (p != 0) {
		cout << p->data;
		p = p->next;
	}
	cout << endl;

	//Node ����
	// Delete from Front
	if (head->data == num) {
		p = head;
		head = head->next;
		delete p;
	}

	// Delete from Middle
	p = head;
	q = head;
	while (p != NULL && p->data != num) {
		q = p;
		p = p->next;
	}
	if (p != NULL) {
		q->next = p->next;
		delete p;
	}
	else
		cout << num << " is not in the list\n";

	// Delete from End
	p = head;
	q = head;
	while(!p->next = NULL) {
		q = p;
		p = p->next;
	}
	q->next = NULL;
	delete p;

	return 0;
}
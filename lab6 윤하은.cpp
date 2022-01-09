////////////////////////////////////////////////////////////////////////
// lab6: Singly Linked List
// Name: Yun Ha Eun
// ID: 20203110
/////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Node {
private:
	int data;
	Node* next;
	Node(int value) { data = value; next = 0; }
	friend class List;
};

class List {
	
private:
	Node* head;
public:
	List() { head = 0; }
	virtual ~List();
	void insert(int);
	void deleteN(int);
	void displayList();
	void search(int); 
	void findMax();
};

void List::insert(int data) {
	Node* p, * q = NULL;
	Node * temp = new Node (data);
	if (head == 0) head = temp;
	else if (temp->data < head->data) {
		temp->next = head;
		head = temp;
	}
	else {
		p = head;
		while ((p != 0) && (p->data < temp->data)) {
			q = p;
			p = p->next;
		}
		if (p != 0) {
			temp->next = p;
			q->next = temp;
		}
		else
			q->next = temp;
	}
}

void List::search(int num) {
	Node* p = NULL;
	if (head != 0) {
		p = head;
		while (p != 0 && p->data != num) {
			p = p->next;
		}
		if (p != 0)
			cout << num << " is found" << endl;
		else
			cout << num << " is not found" << endl;
	}
	else
		cout << "List is empty!" << endl;
}

void List::findMax() {
	Node* p = NULL;
	p = head;
	Node* max = p;
	head = p;
	while (p->next != NULL) {
		p = p->next;
		if (max < p)//->next)
			max = p;//>next;
	}
	printf("Max number is %p\n", *max);
	//cout << "Max number is " << *max << endl;
}

void List::deleteN(int num) {
	Node* p, * q = NULL;
	if (head == 0) cout << "List is empty!" << endl;
	else if (head->data == num) {
		p = head;
		head = head->next;
		delete p;
	}
	else {
		p = head;
		while (p != 0 && p->data != num) {
			q = p;
			p = p->next;
		}
		if (p != 0) {
			q->next = p->next;
			delete p;
		}
		else
			cout << num << " is not in the list" << endl;
	}
}
 
List ::~List()
{
	Node * p;
	while (head != 0) {
		p = head;
		head = head->next;
		delete p;
	}
}


void List::displayList() {
	Node * p;
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

int main(void) {
	List list;
	int a;
	int data;
	while (1) {
		cout << "1. insert 2. delete 3. search 4. FindMax 5. Quit => ";
		cin >> a;
		switch (a) {
		case 5:
			list.~List();
			exit(1);
		case 4:
			list.findMax();
			break;
		case 3:
			cout << "Enter a number => ";
			cin >> data;
			list.search(data);
			break;
		case 2:
			cout << "Enter a number => ";
			cin >> data;
			list.deleteN(data);
			break;
		case 1:
			cout << "Enter a number => ";
			cin >> data;
			list.insert(data);
			break;
		}
		list.displayList();
	}
	return 0;
}
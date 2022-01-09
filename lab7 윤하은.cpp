
////////////////////////////////////////////////////////////////////////
// lab7: Linked Stack & Queue 
// Name: Yun Ha Eun
// ID: 20203110
/////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class Node {
	friend class linkedStack;
	friend class linkedQueue;
	friend class linkedList;

private:
	int data;
	Node* next;
	Node(int value) { data = value; next = 0; }
};

class linkedStack {
private:
	Node* top;
public:
	linkedStack() { top = 0; }
	~linkedStack();
	void createStack();
	void push(int);
	int pop();
	int isEmpty();
	void displayStack();
	void searchStack(int);
};

class linkedQueue {
private:
	Node* front;
	Node* rear;
public:
	linkedQueue() { front = 0; rear = 0; }
	~linkedQueue() {};
	void createQueue();
	void enqueue(int);
	int dequeue();
	int isEmpty();
	void displayQueue();
};

class linkedList {
private: Node* head;
public:
	linkedList() { head = 0; }
	~linkedList() { };
	void insert(int);
	int is_empty();
	void display();
};

void linkedList::insert(int data) {
	Node* temp = new Node(data);
	Node* p, * q = NULL;
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

int linkedList::is_empty() {
	if (head == 0)
		return 1;
	else
		return 0;
}

void linkedList::display() {
	Node* p;
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

int linkedQueue::isEmpty()
{
	if (front == 0) return 1;
	else return 0;
}


void linkedQueue::createQueue()
{
	front = 0; rear = 0;
}

void linkedQueue::enqueue(int data)
{
	Node* temp = new Node(data);
	if (front == 0) { // 큐가 empty 인경우 front rear
		front = temp;
		rear = temp; 
	}
	else {
		rear->next = temp;
		rear = temp;
	}
}

int linkedQueue::dequeue()
{
	Node* p; int num;
	if (!isEmpty()) {
		num = front->data;
		p = front;
		if (front == rear) { front = 0; rear = 0; }
		else front = front->next;
		delete p;
		cout << num << " is dequeued!\n";
		return num;
	}
	//else
		//cout << "Queue is Empty!\n";
}

void linkedQueue::displayQueue()
{
	Node* p;
	if (!isEmpty()) {
		p = front;
		while (p) {
			cout << setw(8) << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
	else
		cout << "Queue is empty!\n";
}

void linkedStack::searchStack(int snum) {
	if (!isEmpty()) {
		Node* p = top;
		while ((p != 0) && p->data != snum)
			p = p->next;

		if (p != 0)
			cout << p->data << " is in the stack\n";
		else
			cout << snum << " is not in the stack\n";
	}
	else
		cout << "Stack is empty!\n";
}


linkedStack::~linkedStack() {
	Node* p;

	while (top != 0) {
		p = top;
		top = top->next;
		delete p;
	}
}

void linkedStack::createStack()
{
	top = 0;
}

int linkedStack::isEmpty()
{
	if (top == 0) return 1;
	else return 0;
}

void linkedStack::push(int data)
{
	Node* temp = new Node(data);
	if (top == 0)
		top = temp;
	else {
		temp->next = top;
		top = temp;
	}
}

void linkedStack::displayStack()
{
	Node* p;
	if (!isEmpty()) {
		p = top;
		while (p) {
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
	else
		cout << "Stack is empty!\n";
}

int linkedStack::pop() //////////////////////////is empty
{
	Node* p; int num;
	if (!isEmpty()) {
		num = top->data;
		p = top;
		top = top->next;
		delete p;
		cout << num << " is popped!\n";
		return num;
	}

}

int main() {
	linkedStack s1;
	linkedQueue q1;
	linkedList l1;
	int a;
	int data = 1;
	while (true) {
		cout << "1. PUSH, 2.POP, 3. ENQUEUE, 4.DEQUE, 5. MakeList. 6. Quit  => ";
		cin >> a;
		// /*
		switch (a) {
		case 6:
			s1.~linkedStack();
			q1.~linkedQueue();
			exit(1);
		case 5:
			while (!s1.isEmpty()) {
				data = s1.pop();
				l1.insert(data);
			}
			while (!q1.isEmpty()) {
				data = q1.dequeue();
				l1.insert(data);
			}
			cout << "List : ";
			l1.display();
			break;
		case 4:
			q1.dequeue();
			cout << "Queue : ";
			q1.displayQueue();
			break;
		case 3:
			cout << "Enter a number => ";
			cin >> data;
			q1.enqueue(data);
			cout << "Queue : ";
			q1.displayQueue();
			break;
		case 2:
			s1.pop();
			cout << "Stack : \n";
			s1.displayStack();
			break;
		case 1:
			cout << "Enter a number => ";
			cin >> data;
			s1.push(data);
			cout << "Stack : \n";
			s1.displayStack();
			break;
		}
		
	}
	return 0;
}

/*

linkedQueue::~linkedQueue() {
	Node* p;

	while (front == rear) {
		p = front;
		p = front->next;
		delete p;
	}
}


void linkedQueue::searchQueue(int num) {
	if (!isEmpty) {
		Node* p = front;
		while (p != 0 && p->data != num) {
			p = p->next;
			if (p != 0)
				cout << p->data << "is in the queue\n";
			else
				cout << num << "is not in the queue\n";
		}
	}
	else
		cout << "Queuze is empty!\n"
}

linkedQueue::~linkedQueue() {
	Node* p;

	while (isEmpty) {//front == 0) {
		p = front;
		front = front->next;
		delete p;
	}
}

*/
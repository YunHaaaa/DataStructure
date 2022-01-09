#include <iostream>
#include <string.h>
#include <string>
using namespace std;

class Node {
	friend class linkedStack;
private:
	int data;
	Node* next;
	Node(int value) {data = value; next = 0;}
};

class linkedStack {
private:
	Node* head;
public:
	linkedStack() { head = 0; }
	~linkedStack();
	void createStack();
	void push(int);
	int pop();
	int isEmpty();
	void displayStack();
	void searchStack(int);
};

void linkedStack::searchStack(int snum) {
	if(!isEmpty()) {
		Node* p = head;
		while ((p != 0) && p->data != snum) 
			p = p->next;
	
		if (p != 0)
			cout << p->data << " is in the list\n";
		else
			cout << snum << " is not in the list\n";
	}
	else
		cout << "List is empty!\n";
	}


linkedStack::~linkedStack() {
	Node* p;

	while (head != 0) {
		p = head;
		head = head->next;
		delete p;
	}
}

void linkedStack::createStack()
{
	head = 0;
}

int linkedStack::isEmpty()
{
	if (head == 0) return 1;
	else return 0;
}

void linkedStack::push(int data)
{
	Node* temp = new Node(data);
	if (head == 0)
		head = temp;
	else {
		temp->next = head;
		head = temp;
	}
}

void linkedStack::displayStack()
{
	Node* p;
	if (!isEmpty()) {
		p = head;
		while (p) {
			cout << p->data;
			p = p->next;
		}
		cout << endl;
	}
	else
		cout << "Stack is empty!\n";
}

int linkedStack::pop()
{
	Node* p; int num;
	num = head->data;
	p = head;
	head = head->next;
	delete p;
	return num;
}

int main() {
	linkedStack s1;
	char input[10]; int num;
	int stopflag = 1;
	while (stopflag) {
		cout << "Command : push, pop, display, search, quit = > "; 
			cin >> input;
		if (strcmp(input, "push") == 0) {
			cout << "Input a number => ";
			cin >> num;
			s1.push(num);
		}
		else if (strcmp(input, "pop") == 0) {
			if (!s1.isEmpty()) {
				num = s1.pop();
				cout << num << " has been popped" << endl; 
			}
			else
				cout << "Stack is empty!\n";
		}
		else if (strcmp(input, "search") == 0) {
			cout << "Enter a number => ";
			cin >> num;
			s1.searchStack(num);
		}
		else if (strcmp(input, "display") == 0)
			s1.displayStack();
		else if (strcmp(input, "quit") == 0)
			stopflag = 0;
		else
			cout << "Bad command" << endl;
	}
	return 0;
}
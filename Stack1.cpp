#include <iostream>

using namespace std;

const int MaxSize = 4;



class Stack {
private:
	int stack[MaxSize];
	int top;
public:
	Stack() { top = -1; }
	void push(int val) {
		stack[++top] = val;
	}
	int pop() {
		return stack[top--];
	}
	bool isEmpty() {
		return top == -1;
	}
	bool isFull() {
		return top == MaxSize - 1;
	}
	void displayStack();
};

void Stack::displayStack() {
	int sp = top;
	while (sp != -1) {
		cout << stack[sp--];
	}
	cout << endl;
}

int main(void) {

	Stack s1;
	s1.push(10);
	s1.push(20);
	s1.push(30);
	s1.push(40);
	s1.displayStack();

	if (s1.isFull())
		cout << "Stack is full\n";

	cout << "Pop: " << s1.pop() << endl;
	cout << "Pop: " << s1.pop() << endl;
	cout << "Pop: " << s1.pop() << endl;
	cout << "Pop: " << s1.pop() << endl;

	if (s1.isEmpty())
		cout << "Stack is empty\n";

	return 0;
}

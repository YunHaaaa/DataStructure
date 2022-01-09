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

void postfix(Stack s) {
	int top = 0;
	s[0] = '\0';
	//get_expression();
}

int main(void) {

	Stack s1;
	postfix(&s1);

	return 0;
}




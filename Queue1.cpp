#include <iostream>

using namespace std;
const int QueueSize = 100;

template <class Type>

class Queue {
private:
	int front;
	int rear;
	int flag;
	Type queue[QueueSize];
public:
	Queue() {
		front = 0; rear = 0; flag = 0;
	}
	virtual ~Queue();
	void enQueue(Type value);
	int deQueue();
	bool isFull();
	bool isEmpty();
	void print();
};

template <class Type>
void Queue<Type>::enQueue(Type item) {
	if (rear == QueueSize - 1) { // MAX_QUEUE_SIZE
		isFull();
		return;
	}
	queue[++rear] = item;
}

template <class Type>
int Queue<Type>::deQueue() {
	if (front == rear)
		return isEmpty();
	return queue[++front];
}

template <class Type>
bool Queue<Type>::isFull() {
	if (rear == QueueSize - 1)
		return true;
	else return false;
}

template <class Type>
bool Queue<Type>::isEmpty() {
	if (front == rear)
		return true;
	else return false;
}

template <class Type>
void Queue<Type>::print() {
	if (isEmpty())
		cout << "Queue is Empty!\n";
	else {
		int i = front + 1;
		cout << "--Print Queue--\n";
		while (i <= rear) {
			cout << queue[i];
			i += 1;
		}
	}
}

int main() {
	Queue <int> q1;

	q1.enQueue(10);
	q1.enQueue(20);
	q1.print();
	cout << q1.isFull() << endl;

	q1.deQueue();
	q1.deQueue();

	cout << q1.isEmpty() << endl;

	q1.print();

	return 0;
}
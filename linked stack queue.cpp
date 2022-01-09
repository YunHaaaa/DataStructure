////////////////////////////////////////////////////////////////////////
// Quiz1
// Name: Yun Ha Eun
// ID: 20203110
// Description1 :
//   Linked Stack과 Linked Queue에 각각 데이터를 입력하고 이 데이터들을 
//   Merge 하여 Linked List로 만들어 출력하는 프로그램
// Description2 :
//   데이터 파일을 읽고, 각 라인별로 데이터들이 palindrome인지 판단하는
//   프로그램 (스택 이용)
// Functions :
//   linkedList
//		Insert - node를 삽입
//		rmvMax - 값이 가장 큰 node를 삭제
//		invert - node 순서를 반대로 변경
//		display - Printout the list
//		is_empty - 리스트가 비었는지 확인
//	 linkedQueue
//		createQueue - queue를 생성
//		enqueue - rear에 node삽입
//		dequeue - front의 node 삭제
//		isEmpty - Queue가 비었는지 확인
//		displayQueue - Printout Queue
//   linkedStack
//		createStack - stack을 생성
//		push - top에 node 삽입
//		pop - top 원소를 제거하고 포인터를 반환
//		isEmpty - stack이 비었는지 확인
//		displayStack - Printout Stack
//   palindrome
/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

#define max 80 // define stack size

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
	void rmvMax();
	void invert();
};

// invert - node 순서를 반대로 변경
void linkedList::invert() {
	Node* p = head, * q = 0, * r;
	while (p) {
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}
	head = q;
}

//Insert - node를 삽입
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

// is_empty - 리스트가 비었는지 확인
int linkedList::is_empty() {
	if (head == 0)
		return 1;
	else
		return 0;
}

// display - Printout the list
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

// isEmpty - Queue가 비었는지 확인
int linkedQueue::isEmpty()
{
	if (front == 0) return 1;
	else return 0;
}

// createQueue - queue를 생성
void linkedQueue::createQueue()
{
	front = 0; rear = 0;
}

// enqueue - rear에 node삽입
void linkedQueue::enqueue(int data)
{
	Node* temp = new Node(data);
	if (front == 0) { // Queue가 empty 인경우 front rear
		front = temp;
		rear = temp;
	}
	else {
		rear->next = temp;
		rear = temp;
	}
}

// dequeue - front의 node 삭제
int linkedQueue::dequeue()
{
	Node* p; int num;
	if (!isEmpty()) {
		num = front->data;
		p = front;
		if (front == rear) { front = 0; rear = 0; }
		else front = front->next;
		delete p;
		return num;
	}
	//else
		//cout << "Queue is Empty!\n";
}

// displayQueue - Printout Queue
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

linkedStack::~linkedStack() {
	Node* p;

	while (top != 0) {
		p = top;
		top = top->next;
		delete p;
	}
}

// createStack - stack을 생성
void linkedStack::createStack()
{
	top = 0;
}

// isEmpty - stack이 비었는지 확인
int linkedStack::isEmpty()
{
	if (top == 0) return 1;
	else return 0;
}

// push - top에 node 삽입
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

// displayStack - Printout Stack
void linkedStack::displayStack()
{
	Node* p;
	int s = 1;
	if (!isEmpty()) {
		p = top;
		while (p) {
			cout << setw(5) << s <<" : " << p->data;
			p = p->next;
			s++;
		}
		cout << endl;
	}
	else
		cout << "Stack is empty!\n";
}

// pop - top 원소를 제거하고 포인터를 반환
int linkedStack::pop()
{
	Node* p; int num;
	if (!isEmpty()) {
		num = top->data;
		p = top;
		top = top->next;
		delete p;
		return num;
	}
}

// rmvMax - 값이 가장 큰 node를 삭제
void linkedList::rmvMax() {
	Node* p, *q;
	p = head;
	q = head;
	Node* Max = p;
	head = p;
	while (p->next != NULL) {
		q = p;
		p = p->next;
		if (Max->data < p->data) {
			Max = p;
		}
	}
	if (head->data == Max->data) { // delete head
		p = head;
		head = head->next;
		delete p;
	}
	else {//delete middle node
		q->next = p->next;
		delete p;
	}
}

bool PChecker(char buffer[]);
int balanced = 0, unbalanced = 0, mismatched = 0;
//char buffer[];

ifstream infile;
bool check = true; // palindrom인지 체크
char buffer[80]; // 데이터 파일을 읽어 저장
int length; // buffer의 길이 저장


int main() {
	linkedStack s1;
	linkedQueue q1;
	linkedList l1;
	int a;
	int data = 1;

	linkedStack s2;
	while (true) {
		cout << "1. PUSH, 2. ENQUEUE, 3. MERGE, 4.Invert, 5. RemoveMax. 6. Quit  => ";
		cin >> a;
		switch (a) {
		case 6:
			cout << "<< quiz1-2: Palindrome using stack >>" << endl;

			infile.open("Quiz1.txt", ios::in); // check file open error
			if (infile.fail()) { cout << "can't open the input file\n" << endl; exit(1); }

			while (infile.getline(buffer, 80)) { // check line by line
				length = strlen(buffer);
				s2.createStack();
				int k = 0;
				
				if (length % 2 == 0) // length가 짝수이면
					while (k < (length / 2)) { //length의 반만큼 PUSH. ‘abccba’ 의 경우 push a, push b, push c.
						s2.push(buffer[k++]);
					}
				else if (length % 2 != 0) { // if len is ODD – 홀수이면
					while (k < (length / 2)) { //length의 반만큼 PUSH. ‘abckcba’의 경우 push a, push b, push c.
						s2.push(buffer[k++]);
					} // 이젠 buffer 에 kcba 남았음
					k++; // k를 건너 뛴다.
				}
				// stack 에서 pop 한 데이터와, buffer(데이터) 와 비교. if same, 다음 글자 비교, 다르면 error message
				while (!s2.isEmpty()){//buffer[j] != '\0') {//(end of line 까지 비교
					char p = s2.pop();
					if (int(buffer[k]) != p) {
						check = false;
					}
					k++;
				}

				if (check == true) {
					printf("palindrome\n");
				}
				else
					printf("Not palindrome\n");
			}
			cout << endl;

			s1.~linkedStack();
			q1.~linkedQueue();
			exit(1);
		case 5:
			l1.rmvMax();
			l1.display();
			break;
		case 4:
			l1.invert();
			l1.display();
			break;
		case 3:
			while (!s1.isEmpty()) {
				data = s1.pop();
				l1.insert(data);
			}
			while (!q1.isEmpty()) {
				data = q1.dequeue();
				l1.insert(data);
			}
			l1.display();
			break;
		case 2:
			cout << "Enter a number => ";
			cin >> data;
			q1.enqueue(data);
			cout << "Queue : ";
			q1.displayQueue();
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

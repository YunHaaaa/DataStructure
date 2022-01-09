////////////////////////////////////////////////////////////////////////
// HW3:Doubly Linked List (DLL)
// Name: Yun Ha Eun
// ID: 20203110
// Description :
//   Test function that use Doubly Linked List
// Functions :
//   Insert - node를 current의 앞, 뒤 / list의 맨 앞, 맨 뒤에 삽입
//   DeleteCurrent - current node를 삭제
//   LocateCurrent - 원하는 위치를 입력받아 current를 변경, 해당 데이터 출력
//   UpdateCurrent - current가 위치한 데이터의 값 교체
//   DisplayList - Printout the list
//   isEmpty - 리스트가 비었는지 확인
// Variables :
//   Pointer head - 리스트의 첫번째 노드
//   Pointer current - 현재위치 노드
//   Pointer next - Node에 연결, 다음 node를 나타내는 링크
//   Pointer prev - Node에 연결, 이전 node를 나타내는 링크
//	 size - 리스트의 길이
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
	Node<Type>* head; // 리스트의 첫번째 노드
	Node<Type>* current; // 현재위치 노드
	int size = 0;
	// 메뉴의 모든 action 이후에는 해당 노드가 current position이 됨
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
	
	int isEmpty() { return (head == 0); } // 연결 리스트가 비었는지 여부를 검사

	void displayList(int); // 연결 리스트의 각 노드들을 출력하는 함수
};

////////////////////////////////////////////////////////////////
// function : insertAfter
// - insert할 데이터를 입력받는다
// - data를 저장한 새로운 노드 생성
// - current node뒤에 insert
// - insert된 노드를 current node로 변경
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
// - insert할 데이터를 입력받는다
// - data를 저장한 새로운 노드 생성
// - current node앞에 insert
// - insert된 노드를 current node로 변경
////////////////////////////////////////////////////////////////

template <class Type>
void List<Type>::insertBefore(Type data) {
	Node<Type>* temp = new Node<Type>(data);
	Node<Type>* p, * q;
	if (isEmpty())
		head = temp;
	else if (current = head)
		// insert in the front & head 이동 = head node 앞에 insert
		insertFirst(data);
	else {
		// insert in the middle & last  = 이동 후 insert
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
// - insert할 데이터를 입력받는다
// - data를 저장한 새로운 노드 생성
// - list의 맨 앞에 노드 위치, head 이동
// - insert된 노드를 current node로 변경
////////////////////////////////////////////////////////////////

template <class Type>
void List<Type>::insertFirst(Type data) {
	Node<Type>* temp = new Node<Type>(data);
	if (isEmpty())
		head = temp;
	else {
		// head node 앞으로 temp node insert
		temp->next = head;
		head->prev = temp;
		head = temp;
	}
	current = temp;
	size++;
}

////////////////////////////////////////////////////////////////
// function : insertLast
// - insert할 데이터를 입력받는다
// - data를 저장한 새로운 노드 생성
// - list의 가장 마지막에 노드 위치
// - insert된 노드를 current node로 변경
////////////////////////////////////////////////////////////////

template <class Type>
void List<Type>::insertLast(Type data) {
	Node<Type>* p, * q;
	Node<Type>* temp = new Node<Type>(data);
	if (isEmpty())
		head = temp;
	else {
		//find last node & insert - p = head, while 문으로 p 이동
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
// - current node 삭제
// - 삭제된 노드의 바로 전이나 뒤의 node를 current node로 변경
////////////////////////////////////////////////////////////////

template <class Type>
void List<Type>::deleteCurrent() {
	Node<Type>* p;
	if (isEmpty())
		cout << "List Empty";
	else if (current == head) {
		// head node 삭제, head 이동
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
		// 마지막 노드 삭제
		current->prev->next = 0;
		p = current;
		current = current->prev;
		delete(p);
	}
	size--;
}

////////////////////////////////////////////////////////////////
// function : locateCurrent
// - 이동할 위치를 입력받는다
// - 해당 위치에 있는 data출력
// - 해당 node를 current node로 변경
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
// - insert할 데이터를 입력받는다
// - 현재 current가 위치한 데이터의 값을 입력받은 값으로 교체
////////////////////////////////////////////////////////////////

template <class Type>
void List<Type>::updateCurrent(Type newdata) {
	current->val = newdata;
}

////////////////////////////////////////////////////////////////
// function : displayList
// - 전체 리스트 출력
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

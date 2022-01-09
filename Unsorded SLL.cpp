#include <iostream>
#include <iomanip>
using namespace std;


template <class Type>
class List {
private:
	int *head;
	int *current;
	//Node* head;
	//Node* current;
public:
	List() { head = 0; current = 0; }
	virtual ~List();
	void insertafter(Type, int); void insertbefore(Type, int);
	void insertfirst(Type, int); void insertlast(Type, int);
	void deleteCurrent(); void locateCurrent(int);
	void updateCurrent(Type); Type retrieveCurrent();
	void displayList(); int listLength(); int is_empty();
};

template <class Type>
class Node {
private:
	Type val;
	Node* next;
	Node(Type data) { val = data; next = 0; }
	friend class List<Type>;
};

template <class Type>
void List<Type>::insertafter(Type data, int num) {
	Node<Type>* p;
	Node<Type>* temp = new Node <Type> (data);
	temp->data = num;
	p->next = NULL;
	if (head == NULL) {
		temp->next = current->next;
		current->next = temp;
		current = temp;
	}
}


template <class Type>
List<Type>::~List()
{
	Node<Type>* p;
	while (head != 0) {
		p = head;
		head = head->next;
		delete p;
	}
}

template <class Type>
void List<Type>::insertbefore(Type data, int num) {
	Node<Type>* p;
	Node<Type>* temp = new Node <Type>(data);
	temp->data = num;
	p->next = NULL;
	if (current == head) {
		temp->next = head;
		head = temp;
		current = temp;
	}
	else {
		p->next = temp;
		temp->next = current;
		current = temp;
	}
}

template <class Type>
void List<Type>::insertlast(Type data,int num) {
	Node<Type>* temp = new Node <Type>(data);
	Node<Type>* p;
	if (head == 0) head = temp;
	else {
		p = head;
		while (p->next != 0)
			p = p->next;
		p->next = temp;
	}
	current = temp;
}

template <class Type>
void List<Type>::deleteCurrent() {
	Node<Type>* p, * q;
	if (head == 0) cout << "List is empty!" << endl;
	else {
		p = current;
		if (head == current) {
			head = head->next; current = current->next;
		}
		else {
			q = head;
			while (q->next != current)
				q = q->next;
			q->next = current->next;
			if (current->next != 0)
				current = current->next;
			else current = head;
		}
		delete p; // p = current
	}//end of else
}

template <class Type>
int List<Type>::is_empty()
{
	if (head == 0) return 1;
	else return 0;
}

template <class Type>
void List<Type>::displayList() {
	Node<Type>* p;
	p = head;
	while (p) {
		cout << setw(8) << p->data;
		p = p->next;
	}
	cout << endl;
}

int main(void) {

	return 0;
}
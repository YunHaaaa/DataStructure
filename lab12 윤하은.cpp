////////////////////////////////////////////////////////////////////////
// lab12: Hashing
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
	Node* link;
	Node(int value) { data = value; link = 0; }
	friend class Htable;
};

class Htable {

private:
	Node* head;
	Node* HT[7];
public:
	int MaxSize = 7;
	Htable() { head = 0; for (int i = 0; i < MaxSize; i++) HT[i] = 0; }
	virtual ~Htable();
	bool findkey(int);
	int insertkey(int);
	int deletekey(int);
	void printable();
	int hash(int key) { return key % MaxSize; }

};


int Htable::insertkey(int data) {
	Node* p, * r = NULL;
	Node* q = new Node(data);

	int index = hash(data);
	bool check = findkey(data);

	if (check == true)
		return false;

	if (HT[index] == NULL) {
		HT[index] = q;
	}
	else {
		r = HT[index];
		p = r;
		while (p->link != NULL)
			p = p->link;
		p->link = q;
	}
	cout << "Hash value " << index << endl;
}

bool Htable::findkey(int key) {
	Node* p, * q = NULL;
	
	int index = hash(key);
	p = HT[index];
	if (p == NULL) {
		return false;
	}
	else {
		q = p;
		while ((q != NULL) && q->data != key)
			q = q->link;
		if (q == NULL){
			return false;
		}
		else {
			return true;
		}
	}
}

int Htable::deletekey(int key) {
	Node* p, * q = NULL;
	bool check = findkey(key);
	int index;

	if (check == false) {
		cout << "Hash value " << key << " Key is not found" << endl;
		return false;
	}
	else {
		index = hash(key);
		head = HT[index];
		if (head->data == key) {
			// move head= head->next;
			// = delete & update head node
			p = head;
			head = head->link;
			HT[index] = head;
			delete p;
		}
		else {
			//p, q = head & ÀÌµ¿
			// find node and delete the node for the key
			p = head;
			while (p != 0 && p->data != key) {
				q = p;
				p = p->link;
			}
			if (p != 0) {
				q->link = p->link;
				HT[index] = q;
				delete p;
			}
			else
				cout << key << " is not in the list" << endl;
		}
	}
}

Htable::~Htable()
{
	Node* p;
	while (head != 0) {
		p = head;
		head = head->link;
		delete p;
	}
}


void Htable::printable() {
	Node* p;
	for (int i = 0; i < MaxSize; i++) {
		cout << "HashT[" << i << "] -> ";
		p = HT[i];
		for (p; p != NULL; p = p->link)
			if (p != NULL)
				cout << p->data << " ";
		cout << endl;
	}
}

int main(void) {
	Htable h;
	int a;
	int key;
	while (1) {
		cout << "1. insert 2. delete 3. find 4. Quit => ";
		cin >> a;
		switch (a) {
		case 4:
			h.~Htable();
			exit(1);
		case 3:
			cout << "Enter key ";
			cin >> key;
			if (h.findkey(key))
				cout << "Hash value " << key << " Key is found" << endl;
			else
				cout << "Hash value  " << key << "Key is not found" << endl;			
			break;
		case 2:
			cout << "Enter key ";
			cin >> key;
			h.deletekey(key);
			break;
		case 1:
			cout << "Enter key ";
			cin >> key;
			h.insertkey(key);
			break;
		}
		h.printable();
	}
	return 0;
}
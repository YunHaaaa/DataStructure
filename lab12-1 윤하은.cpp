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
	int empty = true;
	Node(int value) { data = value; link = 0; }
	friend class Htable;
};

class Htable {

private:
	Node* head = NULL;
	Node* htable[7];
public:
	int MaxSize = 7;
	int key = 0;
	Htable();
	virtual ~Htable();
	bool findkey(int);
	int insertkey(int);
	int deletekey(int);
	void printable();
	int hash(int key) { return key % MaxSize; }

};

Htable::Htable() {
	head = 0;
	for (int i = 0; i < MaxSize; i++) {
		htable[i] = NULL;
	}
}

int Htable::insertkey(int data) {
	Node* p, * r = NULL;
	Node* q = new Node(data);
	cout << data << endl;

	int index = hash(data);
	bool check = findkey(data);

	if (check == true) {
		return false;
	}
	if (htable[index] == NULL) {
		htable[index] = q;
		htable[index]->empty = false;
	}
	else {
		r = htable[index];
		p = r;
		while (p->link != NULL)
			p = p->link;
		p->link = q;
	}
	cout << "Hash value " << index << endl;
	return true;
}

bool Htable::findkey(int key) {
	Node* p = NULL, * q = NULL;

	int index = hash(key); // get index
	int start = 0;
	bool found = false;
	bool loop = false;
	if (htable[index] == NULL)
		return false;
	while ((htable[index]->empty) && (found == false) && (loop == false)) { //empty yet
		
		if (htable[index]->data == key)
			found = true; // key is found 
		else {
			index = (index + 1) % MaxSize; // linear probing
			if (index == start)
				loop = true; // exit condition }
		}
		cout << found << endl;
		return found;
	}
}

int Htable::deletekey(int key) {
	bool check = findkey(key);
	int index = hash(key);

	if (check == false) {
		cout << "Hash value " << key << " Key is not found" << endl;
		return false;
	}
	else {
		htable[index]->empty = true;
		return true;
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
		p = htable[i];
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
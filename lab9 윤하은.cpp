////////////////////////////////////////////////////////////////////////
// lab9 : MAX HEAP Implementation & HEAP SORT
// Name: Yun Ha Eun
// ID: 20203110
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
template <class KeyType> class MaxHeap;

#define swap(a, b ,t) {t = a; a = b; b = t;}

template <class KeyType>
class MaxHeap {
	KeyType* heap;
	int MaxSize = 0; // Heap의 최대 크기
	void adjust(int i, int* n);
public:
	int n; // 최대 Heap의 현재 크기
	MaxHeap(int sz);
	~MaxHeap() {};
	void Insert(KeyType item, int* n);
	void firstInsert(KeyType item, int* n);
	void Delete(int* n);
	void Make(int* n);
	void Sort(int* n);
	void Print(int* n);
	void Search(KeyType item, int* n);
	void Level(int* n);
	bool HeapFull(int* n);
	bool HeapEmpty(int* n);
};

template <class KeyType>
void MaxHeap<KeyType>::Search(KeyType item, int* n) {
	for (int i = 1; i <= MaxSize; i++) {
		if (item == heap[i]) {
			cout << item << " is found" << endl << endl;
			return;
		}
	}
	cout << item << " is not found" << endl << endl;
}

template <class KeyType>
void MaxHeap<KeyType>::Level(int* n) {
	int size = *n;
	int level = 0;
	while (size != 0) { 
		size = size / 2;
		level++; 
	}
	cout <<"level of heap is " << level << endl << endl;
}


template <class KeyType>
void MaxHeap<KeyType>::adjust(int i, int* n) {
	int child;
	child = 2 * i;
	KeyType temp = heap[i];
	while (*n >= child) {
		if (*n > child && heap[child] < heap[child + 1])
			child += 1;
		if (temp >= heap[child])
			break;
		heap[child / 2] = heap[child];
		child = 2 * child;
	}
	heap[child / 2] = temp;
	return;
}

template <class KeyType>
MaxHeap<KeyType>::MaxHeap(int sz) {
	MaxSize = sz;
	n = 0;
	heap = new KeyType[MaxSize + 1];//element<KeyType>[MaxSize+1]
	for (int i = 1; i <= MaxSize; i++) {
		heap[i] = 0;
	}
}


template <class KeyType>
void MaxHeap<KeyType>::firstInsert(KeyType item, int* n) {
	int i;
	if (HeapFull(n)) {
		cout << "Heap is full..." << endl;
		return; //error
	}
	i = ++(*n);
	//item을 heap에 삽입
	heap[i] = item;
}

template <class KeyType>
void MaxHeap<KeyType>::Insert(KeyType item, int* n) {
	int i;
	if (HeapFull(n)) {
		cout << "Heap is full..." << endl;
		return; //error
	}
	i = ++(*n);
	//item을 heap에 삽입
	while ((i > 1) && (item > heap[i / 2])) {
		heap[i] = heap[i / 2];
		i = i / 2;
	}
	heap[i] = item;
}

template <class KeyType>
void MaxHeap<KeyType>::Delete(int* n) {
	int parent, child;
	KeyType item, temp;//element<KeyType> item, temp;
	if (HeapEmpty(n)) {
		cout << "Heap is full..." << endl << endl;
		return; //error
	}
	else {
		item = heap[1];
		temp = heap[(*n)--];
		parent = 1;
		child = 2;

		while (child <= *n) {
			if ((child <= *n) && (heap[child] < heap[child + 1]))
				child++;
			if (temp >= heap[child])
				break;
			heap[parent] = heap[child];
			parent = child;
			child = child * 2;
		}
		heap[parent] = temp;
		MaxSize--;
	}
}

template <class KeyType>
void MaxHeap<KeyType>::Make(int* n) {
	for (int i = *n / 2; i > 0; i--) {
		adjust(i, n);
	}
}

template <class KeyType>
void MaxHeap<KeyType>::Sort(int* n) {
	for (int i = *n - 1; i > 0; i--) { // root -> 배열의 뒤쪽으로 heap sort
		int temp = heap[i];
		swap(heap[1], heap[i + 1], temp);
		adjust(1, &i); // root 제거 후 나머지는 heap으로 변환
	}
}

template <class KeyType>
void MaxHeap<KeyType>::Print(int* n) {
	cout << "Heap: ";
	for (int i = 1; i <= *n; i++) {
		cout << heap[i] << " ";
	}
	cout << endl << endl;
}

template <class KeyType>
bool MaxHeap<KeyType>::HeapFull(int* n) {
	if (*n == MaxSize)
		return true;
	return false;
}

template <class KeyType>
bool MaxHeap<KeyType>::HeapEmpty(int* n) {
	if (*n == 0)
		return true;
	return false;
}

int main() {
	MaxHeap<int>* h1 = new MaxHeap<int>(11);
	int a;
	int data;
	h1->firstInsert(26, &(h1->n));
	h1->firstInsert(5, &(h1->n));
	h1->firstInsert(77, &(h1->n));
	h1->firstInsert(1, &(h1->n));
	h1->firstInsert(61, &(h1->n));
	h1->firstInsert(11, &(h1->n));
	h1->firstInsert(59, &(h1->n));
	h1->firstInsert(15, &(h1->n));
	h1->firstInsert(48, &(h1->n));
	h1->firstInsert(19, &(h1->n));

	while (true) {
		cout << "Enter Command : (1.print 2. search 3.leveltest 4.makeheap 5.heapsort 6.delete 7.insert 8.quit ) ";
		cin >> a;
		switch (a) {
		case 8:
			h1->~MaxHeap();
			exit(1);
		case 7:
			cout << "Enter a number => ";
			cin >> data;
			h1->Insert(data, &(h1->n));
			h1->Print(&(h1->n));
			break;
		case 6:
			h1->Delete(&(h1->n));
			h1->Print(&(h1->n));
			break;
		case 5:
			h1->Sort(&(h1->n));
			cout << "Sort 결과 : ";
			h1->Print(&(h1->n));
			break;
		case 4:
			h1->Make(&(h1->n));
			cout << "Heap 변환 : ";
			h1->Print(&(h1->n));
			break;
		case 3:
			h1->Level(&(h1->n));
			break;
		case 2:
			cout << "Enter a number => ";
			cin >> data;
			h1->Search(data, &(h1->n));
			break;
		case 1:
			h1->Print(&(h1->n));
			break;
		}
	}
	return 0;
}
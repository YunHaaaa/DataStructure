///////////////////////////////////////////////////////////////////////
// lab10 : Graph Search - (BFS)
// Name: Yun Ha Eun
// ID: 20203110
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdio.h>
#include <iomanip>

using namespace std;


class Node {
	friend class linkedQueue;
private:
	int data;
	Node* next;
public:
	Node(int value) {
		data = value;
		next = 0;
	}
	friend class LinkedQueue;
};

class linkedQueue {
private:
	Node* front;
	Node* rear;
	int visited[7];
	int queue[10];
public:
	linkedQueue() { front = 0; rear = 0; }
	~linkedQueue() {};
	void enqueue(int item);
	int dequeue();
	int isEmpty();
	void printMatrix(int graph[][8], int max);
	void bfs(int v, int graph[][8], int max);

	void printMatrix(int graph[][6], int max);
	void bfs(int v, int graph[][6], int max);
};

void linkedQueue::bfs(int v, int graph[][8], int max) {
	cout << "Breadth First Search -> ";
	for (int i = 1; i < max; i++)
		visited[i] = false; // visited 초기화
	visited[v] = true; // 정점 방문시 visited[i]는 true 됨
	enqueue(v);
	while (not isEmpty()) {
		v = dequeue();
		cout << v << " ";
		for (int j = 0; j < max; ++j) { //인접된 모든 노드에 대해
			if (graph[v][j] && !visited[j]) { //if not visited
				visited[j] = true;
				enqueue(j);
			}
		}
	}
	cout << endl;
}

void linkedQueue::bfs(int v, int graph[][6], int max) {
	cout << "Breadth First Search -> ";
	for (int i = 1; i < max; i++)
		visited[i] = false; // visited 초기화
	visited[v] = true; // 정점 방문시 visited[i]는 true 됨
	enqueue(v);
	while (not isEmpty()) {
		v = dequeue();
		cout << v << " ";
		for (int j = 0; j < max; ++j) { //인접된 모든 노드에 대해
			if (graph[v][j] && !visited[j]) { //if not visited
				visited[j] = true;
				enqueue(j);
			}
		}
	}
	cout << endl;
}

int linkedQueue::isEmpty()
{
	if (front == 0) return 1;
	else return 0;
}


void linkedQueue::enqueue(int data)
{
	Node* temp = new Node(data);
	//cout << "enqueue : " << data << endl;
	if (front == 0) { // 큐가 empty 인경우 front rear
		front = temp;
		rear = temp;
	}
	else {
		rear->next = temp;
		rear = temp;
	}
}

int linkedQueue::dequeue()
{
	Node* p; int num;
	if (!isEmpty()) {
		num = front->data;
		p = front;
		if (front == rear) { front = 0; rear = 0; }
		else front = front->next;
		delete p;
		// cout << "dequeue" << num << endl;
		return num;
	}
	else
		cout << "Queue is Empty!\n";
}

void linkedQueue::printMatrix(int graph[][8], int max)
{
	cout << "    ";
	for (int i = 0; i < max; i++) {
		cout << "v" << i << "  ";
	}
	cout << endl;
	for (int i = 0; i < max; i++) {
		cout << "v" << i << "   ";

		for (int j = 0; j < max; j++) {
			cout << graph[i][j] << "   ";
		}
		cout << endl;
	}
}

void linkedQueue::printMatrix(int graph[][6], int max)
{
	cout << "    ";
	for (int i = 0; i < max; i++) {
		cout << "v" << i << "  ";
	}
	cout << endl;
	for (int i = 0; i < max; i++) {
		cout << "v" << i << "   ";

		for (int j = 0; j < max; j++) {
			cout << graph[i][j] << "   ";
		}
		cout << endl;
	}
}


int main() {

	int max1 = 8;
	int graph1[8][8] = {
		0, 1, 1, 0, 0, 0, 0, 0,
		1, 0, 0, 1, 1, 0, 0, 0,
		1, 0, 0, 0, 0, 1, 1, 0,
		0, 1, 0, 0, 0, 0, 0, 1,
		0, 1, 0, 0, 0, 0, 0, 1,
		0, 0, 1, 0, 0, 0, 0, 1,
		0, 0, 1, 0, 0, 0, 0, 1,
		0, 0, 0, 1, 1, 1, 1, 0
	};
	int max2 = 6;
	int graph2[6][6] = {
		0, 1, 1, 0, 0, 0,
		1, 0, 1, 1, 0, 0,
		1, 1, 0, 0, 0, 1,
		0, 1, 0, 0, 1, 1,
		0, 0, 0, 1, 0, 1,
		0, 0, 1, 1, 1, 0
	};
	cout << "******** Adjacency Matrix ********" << endl;
	linkedQueue q1;
	q1.printMatrix(graph1, max1);
	q1.bfs(0, graph1, max1);
	cout << endl << endl << "******** Adjacency Matrix ********" << endl;
	linkedQueue q2;
	q2.printMatrix(graph2, max2);
	q2.bfs(0, graph2, max2);
	return 0;
}


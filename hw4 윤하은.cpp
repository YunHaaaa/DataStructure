///////////////////////////////////////////////////////////////////////
// lab10 : Graph Search (Depth First Search: DFS)
// Name: Yun Ha Eun
// ID: 20203110
// Variables :
//   Pointer head - 리스트의 첫번째 노드
//   array graph - head nodes for each list
//   Pointer next - Node에 연결, 다음 node를 나타내는 링크
//   array visited - 초기값은 false, 방문시 true
// Functions :
//   print_node() - print graph data
//   build_list(char buf[], int line) - build list
//   dfs(int v) - Depth First Search
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iomanip>

using namespace std;


class Node {
	friend class AdjList;
private:
	int data;
	Node* next;
public:
	Node(int value) {
		data = value;
		next = 0;
	}
};

class AdjList {
private:
	//head nodes for each list
	Node* graph[10];
	Node* head;
public:
	// 초기값은 false, 방문시 true
	int visited[10];
	AdjList() {};
	void print_node();
	void build_list(char buf[], int line);
	void dfs(int v);
};

void AdjList::build_list(char buf[], int line) {
	char temp;
	int i = 0;
	// 각 라인별 데이터로 인접리스트 생성
	temp = buf[i++];
	int itemp = temp - '0';
	// 각 리스트의 첫번째 head node 생성
	head = new Node(itemp);
	// head 노드 저장
	graph[line] = head;
	head->next = NULL;

	// q for moving
	Node* q = head;
	while (buf[i] != '\0') {
		temp = buf[i++];
		itemp = temp - '0';
		// create next node 생성
		Node* t = new Node(itemp);
		// & make singly linked list
		q->next = t;
		q = q->next;
	}
}

void AdjList::print_node() {
	Node* p;
	if (head == 0) cout << "List is empty!" << endl;
	else {
		for (int j = 0; graph[j] != NULL; j++) {
			p = graph[j];

			cout <<"  graph[" << j << "]  ->  ";
			p = p->next;
			for (int i = 1; p != NULL; p = p->next) {
				cout << p->data << " ";
			}
			cout << endl;
		}
	}
}

void AdjList::dfs(int v) {
	//시작정점 v 방문
	visited[v] = true;
	Node* w;
	cout << v << " -> ";

	//For each vertex w adjacent to v do
	//if not visited[w] then DFS(w)
	for (w = graph[v]; w != NULL; w = w->next) {
		if (!visited[w->data]) {
			dfs(w->data);
		}
	}
}


int main() {
	AdjList a;
	// Visited 배열을 0 으로 초기화
	for (int i = 0; i < 10; i++) {
		a.visited[i] = false;
	}
	// get data from data file
	ifstream infile;
	char buffer1[80];
	infile.open("hw4.txt", ios::in);
	if (infile.fail()) { cout << "can't open the input file" << endl; exit(1); }
	
	int line = 0, v = 0;
	while (infile.getline(buffer1, 80)) {
		a.build_list(buffer1, line++);
	}
	// print Adjacency Lis
	cout << "<<   Graph data 1   >>\n\n";
	a.print_node();
	// print Adjacency Lis
	cout << "\ndepth first search result :\n";
	a.dfs(v);

	cout << endl << endl << endl;

	AdjList b;
	// Visited 배열을 0 으로 초기화
	for (int i = 0; i < 10; i++) {
		b.visited[i] = false;
	}
	// get data from data file
	ifstream infile2;
	char buffer2[80];
	infile2.open("hw4_2.txt", ios::in);
	if (infile2.fail()) { cout << "can't open the input file" << endl; exit(1); }

	int line2 = 0, v2 = 0;
	while (infile2.getline(buffer2, 80)) {
		b.build_list(buffer2, line2++);
	}
	// print Adjacency Lis
	cout << "<<   Graph data 2   >>\n\n";
	b.print_node();
	// print Adjacency Lis
	cout << "\ndepth first search result :\n";
	b.dfs(v2);

	cout << endl << endl << endl;;
	return 0;
}


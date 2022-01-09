///////////////////////////////////////////////////////////////////////
// Hw5 : Shortest Path
// Name: Yun Ha Eun
// ID: 20203110
// Variables :
//   array distance - v0 ���� S ���� �������� ��ģ vi ������ �ִܰŸ�
//   array cost - <i, j>�� ����ġ
//   array found - �ʱⰪ�� false, �湮�� true
// Functions :
//   printM() - print matrix
//   Shortestpath() - find and print shortest path
//   choose() - find min value node
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
using namespace std;

#define max 999
#define maxn 6


// print cost matrix
void printM(int COST[maxn][maxn]) {
	cout << endl << "******    Adjacency matrix    ******" << endl;
	for (int i = 0; i < maxn; i++) {
		for (int j = 0; j < maxn; j++) {
			cout << setw(5) << COST[i][j];
		}
		cout << endl;
	}
}

// find min value node
int choose(int distance[], int n, bool found[]) {
	int min = max;
	int minnode;
	minnode = NULL;
	for (int i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			minnode = i;
			min = distance[i];
		}
	return minnode;
}

// find and print shortest path
void Shortestpath(int v, int cost[][maxn], int distance[], int n, bool found[]) {
	int u;
	cout << endl << "******      Shortest  Path      ******" << endl;
	cout << "Beginning Dist: ";
	for (int i = 0; i < n; i++) {
		found[i] = false;
		distance[i] = cost[v][i];
		cout << distance[i] << "  "; // print the row for the vertex
	}
	cout << endl << endl;

	found[v] = true; // start vertex mark 
	distance[v] = 0; // start vertex 0

	for (int i = 0; i < n-1; i++) {
		u = choose(distance, n, found); // find min value node
		if (u == NULL)
			u = i+1;
		found[u] = true; // mark that node
		cout << "Select: (" << u << ")  dist:  ";

		for (int w = 0; w < n; w++) { // and replace if revised value
			if (found[w] == false) { // if not marked
				if (distance[u] + cost[u][w] < distance[w]) {//�ʱⰪ ���� ������
					distance[w] = distance[u] + cost[u][w]; // update new value
				}
			}
			cout << setw(5) << distance[w]; // print the row for the vertex
		}
		cout << endl;
	}		
}

int main() {
	bool found[maxn];
	int distance[maxn];

	// ���� �׷���
	int COST1[maxn][maxn] = {
						{ 0, 50, 10, max, 45, max},
						{ max, 0, 15, max, 10, max },
						{ 20, max, 0, 15, max, max },
						{ max, 20, max, 0, 35, max },
						{ max, max, max, 30, 0, max},
						{ max, max, max, 3, max, 0} };
	// ������ �׷���
	int COST2[maxn][maxn] = {
						{ 0, 3, 5, 9, max, max},
						{ 3, 0, 3, 4, 7, max },
						{ 5, 3, 0, 2, 6, 8 },
						{ 9, 4, 2, 0, 2, 2 },
						{ max, 7, 6, 2, 0, 5},
						{ max, max, 8, 2, 5, 0} };
	
	printM(COST1);
	Shortestpath(0, COST1, distance, maxn, found);

	printM(COST2);
	Shortestpath(0, COST2, distance, maxn, found);

	return 0;
}
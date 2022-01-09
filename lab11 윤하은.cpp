///////////////////////////////////////////////////////////////////////
// lab11 : Prim’s Algorithm (Minimal Spanning Tree)
// Name: Yun Ha Eun
// ID: 20203110
////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

#define max 100
#define maxn 7

void printMst(int COST[maxn][maxn]) {
	cout << "******   Weighted  Graph   ******" << endl;
	cout << "     ";
	for (int i = 0; i < maxn; i++) {
		for (int j = 0; j < maxn; j++) {
			if (i == 0)
				cout << "v" << j << "  ";
			else {
				if (j == 0)
					cout << "v" << i << "   ";
				else
					cout << COST[i][j] << "   ";
			}
		}
		cout << endl;
	}
}

void PrimeMst(int COST[maxn][maxn]) {
	int lowcost[maxn];
	int closest[maxn];
	int min, large = 1000, total = 0;
	int k, v = 0;

	cout << "\n***** Minimal Spanning Tree *****\n";

	for (int i = 1; i < maxn; i++) { //COST= adjacency matrix
		lowcost[i] = COST[v][i]; //v= starting vertex (한줄 복사)
		closest[i] = v;
	}
	for (int i = 1; i < maxn; i++) { // while (T contains fewer than n-1 edges)
		min = lowcost[i]; k = i;
		for (int j = 1; j < maxn; j++) { // 최소비용 edge 찾기
			if (lowcost[j] < min)
			{
				min = lowcost[j]; k = j;
			}
		}
		if (i != 1) {
			cout << closest[k] << ", " << k << endl; // 선택된 edge 출력
			total = total + lowcost[k]; // 전체 비용 누적 & marking
		}
		lowcost[k] = large; // 방문한 노드는 큰숫자로 마킹
		for (int j = 1; j < maxn; j++) {
			if (lowcost[j] < large) { //if( COST[k][j] < lowcost[j]&&lowcost[j] < large)
				lowcost[j] = COST[k][j];
				closest[j] = k;
			}
		} //find next edge
	}
	cout << "Total = " << total << endl;
}

int main() {

	int T = { }; //Prime MST TV={0} //start with vertex 0//
	int COST[maxn][maxn] = { { 0, 0, 0, 0, 0, 0 },
						{ 0, max, 6, 1, 5, max, max},
						{ 0, 6, max, 4, max, 3, max },
						{ 0, 1, 4, max, 5, 6, 5 },
						{ 0, 5, max, 5, max, max, 2 },
						{ 0, max, 3, 6, max, max, 6},
						{ 0, max, max, 5, 2, 6, max} };

	printMst(COST);
	PrimeMst(COST);
}
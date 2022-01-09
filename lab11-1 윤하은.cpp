///////////////////////////////////////////////////////////////////////
// lab11-1 : Kruskal Algorithm (Minimal Spanning Tree)
// Name: Yun Ha Eun
// ID: 20203110
////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;


struct inputdata {
	char ff;
	int edges;
	char ll;
}v[100];

struct list_node {
	char vertex;
	struct list_node* link;
}*table[10], * pos1, * pos2, * next;

int comp(char teg1, char teg2) {
	int i = 0;
	while (table[i]->vertex != teg1) {
		i++;
		pos1 = table[i];
	}
	i = 0;
	while (pos1->link != NULL)
		pos1 = pos1->link;
	while (table[i]->vertex != teg2) {
		i++;
		pos2 = table[i];
	}
	while (pos2->link != NULL)
		pos2 = pos2->link;
	if (pos1->vertex == pos2->vertex)
		return 1;
	else 
		return 0;
}

void sort(int j) {
	struct inputdata temp;
	int jj = 0;
	int k = 0;
	k = j;
	do {
		do {
			if (v[jj].edges > v[jj + 1].edges) {
				temp = v[jj];
				v[jj] = v[jj + 1];
				v[jj + 1] = temp;
			}
			jj++;
		} while (jj != k - 1);

		jj = 0;
		k--;
	} while (k != 2);
}

void printK() {
	int count = 1;
	for (int i = 0; i <= 9; i++) {
		cout << "   " << v[i].ff << " " << v[i].edges << " " << v[i].ll << "  ";
		count++;
		if (count == 6)
			cout << endl;
	}
	cout << endl << endl;
}

void kruskal(int j) {
	int count = 1;
	int bol;
	int sum = 0;

	for (int i = 0; i <= j; i++) {
		list_node* next = new list_node();
		table[i] = next;
		table[i]->vertex = 64 + i;
	}

	cout << " 3. Minimum Spanning Tree " << endl << endl;
	int i = 0;
	while (i <= j - 2) {
		bol = comp(v[i].ff, v[i].ll);
		if (bol == 0) {
			cout << "  Edge " << count << ":   ";
			cout << v[i].ff << "  " << v[i].edges << "  " << v[i].ll << endl;
			pos2->link = pos1;
			count++;
			sum += v[i].edges;
		}
		i++;
	}
	cout << endl << " 4. Final cost for kruskal is " << sum << endl << endl;
}


void main() {
	int j = 9, i = 0;
	cout << endl << "  << MST by Kruskal's >> " << endl << endl;

	v[0].ff = 'A';
	v[0].edges = 6;
	v[0].ll = 'B';

	v[1].ff = 'B';
	v[1].edges = 7;
	v[1].ll = 'C';

	v[2].ff = 'A';
	v[2].edges = 1;
	v[2].ll = 'C';

	v[3].ff = 'A';
	v[3].edges = 5;
	v[3].ll = 'D';

	v[4].ff = 'C';
	v[4].edges = 5;
	v[4].ll = 'D';

	v[5].ff = 'B';
	v[5].edges = 3;
	v[5].ll = 'E';

	v[6].ff = 'C';
	v[6].edges = 8;
	v[6].ll = 'E';

	v[7].ff = 'C';
	v[7].edges = 4;
	v[7].ll = 'F';

	v[8].ff = 'D';
	v[8].edges = 2;
	v[8].ll = 'F';

	v[9].ff = 'E';
	v[9].edges = 9;
	v[9].ll = 'F';

	cout << " 1. Input Data : " << endl;
	printK();

	sort(j);
	cout << " 2. Sorted Data : " << endl;
	printK();

	kruskal(j);
}
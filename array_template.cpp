#include <iostream>
using namespace std;

template <class T>
void selectionSort(T* a, int n) {
	int i, j, min;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			if (a[j] < a[min])
				min = j;
			swap(a[i], a[min]);
		}
	}
}

int main() {
	float farray[100] = { 1.2, 0.3, 3.2 };
	int intarray[200] = { 1, 9, 2, 3 };

	selectionSort(farray, 100);
	selectionSort(intarray, 100);

	cout << farray << endl << intarray << endl;
	return 0;
}

// 00F3F884
// OOF3F55C ............?¹¹¾ß...?
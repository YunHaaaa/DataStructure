#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct median {
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    void insert(int data) {
        if (maxHeap.size() == 0) {
            maxHeap.push(data);
            return;
        }
        
        if (maxHeap.size() == minHeap.size()) {
            if (data <= get())
                maxHeap.push(data);
            else
                minHeap.push(data);
            
            return;
        }

        if (maxHeap.size() < minHeap.size()) {
            if(data > get()) {
                maxHeap.push(minHeap.top());
                minHeap.pop();
                minHeap.push(data);
            }
            else
                maxHeap.push(data);
            
            return;
        }

        if (data < get()) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
            maxHeap.push(data);
       }
        else
            minHeap.push(data);
    }

    // ����� ���ҷκ��� �߾Ӱ��� ���Ͽ� ��ȯ
    double get() {
        if (maxHeap.size() == minHeap.size())
            return (maxHeap.top() + minHeap.top()) / 2.0;

        if (maxHeap.size() < minHeap.size())
            return minHeap.top();

        return maxHeap.top();
    }    
};

int main() {
    median med;

    med.insert(1);
    cout << "1 ���� �� �߾Ӱ�: " << med.get() << endl;

    med.insert(5);
    cout << "5 ���� �� �߾Ӱ�: " << med.get() << endl;

    med.insert(2);
    cout << "2 ���� �� �߾Ӱ�: " << med.get() << endl;

    med.insert(10);
    cout << "10 ���� �� �߾Ӱ�: " << med.get() << endl;

    med.insert(40);
    cout << "40 ���� �� �߾Ӱ�: " << med.get() << endl;
    

}
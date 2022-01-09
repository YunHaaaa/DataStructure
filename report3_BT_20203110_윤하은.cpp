/*
 * File Processing, 2021
 * 학번 : 20203110
 * 이름 : 윤하은
 * B-tree implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

/**
  * BTNode represents a node in B-tree.
  */
typedef struct BTNode
{
    int n, * K, * A;
    struct BTNode** P;
} BTNode, * BTree;
//typedef BTNode* BTree;


/**
 * getBTNode returns a new node.
 * @param m: fanout of B-tree
 * @return a new node
 */
BTNode* getBTNode(int m)
{
    BTNode* node = (BTNode*)malloc(sizeof(BTNode));
    if (node) {
        node->n = 0;
        node->K = (int*)malloc(sizeof(int) * (m - 1));
        node->A = NULL;
        node->P = (BTNode**)calloc(m, sizeof(BTNode*));
    }
   
    return node;
}


class Stack {
private:
    int top;
    BTNode* stack;
public:
    int size;
    Stack(int sz = 0);
    ~Stack();
    void push(BTNode node);
    BTNode pop();
    int isEmpty() { return top == -1; }
    int isFull() { return top == size - 1; }
    //friend class BTree;
};

class iStack {
private:
    int top;
    int* istack;
public:
    int size;
    iStack(int sz = 0);
    ~iStack();
    void push(int node);
    int pop();
    int isEmpty() { return top == -1; }
    int isFull() { return top == size - 1; }
    //friend class BTree;
};

Stack::Stack(int sz) {
    stack = new BTNode[sz];
    //	assert(stack != 0);
    top = -1;
    size = sz;
}

Stack::~Stack() {
    delete stack;
}

void Stack::push(BTNode node) {
    if (isFull()) {
        cerr << "Error: push on full stack" << endl;
        exit(-1);
    }
    stack[++top] = node;
}

BTNode Stack::pop() {
    if (isEmpty()) {
        cerr << "Error: pop on empty stack" << endl;
        exit(-1);
    }
    return stack[top--];
}


iStack::iStack(int sz) {
    istack = new int[sz];
    //	assert(stack != 0);
    top = -1;
    size = sz;
}

iStack::~iStack() {
    delete istack;
}

void iStack::push(int node) {
    if (isFull()) {
        cerr << "Error: push on full stack" << endl;
        exit(-1);
    }
    istack[++top] = node;
}

int iStack::pop() {
    if (isEmpty()) {
        cerr << "Error: pop on empty stack" << endl;
        exit(-1);
    }
    return istack[top--];
}

/**
 * binarySearch returns index i where K[i-1] < key <= K[i].
   = 0, 1, 2, ...
 * @param K: an array
 * @param n: size of array(K)
 * @param key: a key to search
 * @return index of key in K
 */
int binarySearch(int K[], int n, int key)
{
    /* write your code here */
    int idx = 0;
    int found = false;
    //root = K[0]

    if (K == NULL)
        return NULL;
    else {
        while (!found) {
            for (idx; idx < n; idx++) {
                if (key == K[idx]) {
                    found = true;
                    return idx;
                }
            }
        }
       
    }
    return idx;
    
}
void split(BTNode q, int s, BTNode ap)
{
    int i;
    ap = *getBTNode(s);
    if (ap.K != NULL) {
        ap.P[0] = q.P[s];
        for (i = s + 1; i <= q.n; i++)       
        {
            ap.K[i - s] = q.K[i];
            ap.P[i - s] = q.P[i];
        }
        ap.n = q.n - s;
        (ap.K) = &(q.K[0]);
        q.K[0] = s - 1;        

    }
}

/**
 * insertBT inserts newKey into T.
 * @param T: a B-tree
 * @param m: fanout of B-tree
   fanout = n
 * @param newKey: a key to insert
 */
void insertBT(BTree T, int m, int newKey)
{
    BTNode x;
    if (T)
        x = *T;
    else
        x = *getBTNode(m);
    BTNode y = *getBTNode(m);
    Stack stack;
    iStack istack;
    int i;
    // find position to insert newKey while storing parent node on stack
    while (x.K != NULL) {
        i = binarySearch(x.K, m, newKey);

        if ((i < x.n) && (newKey == x.K[i]))
            return;

        stack.push(x);
        istack.push(i);

        x = *x.P[i];
    }

    // insert key and node while popping parent node from stack
    while (!stack.isEmpty()) {
        x = stack.pop();
        i = istack.pop();

        if (x.n < m - 1) {
            //insert newKey into x.K;
            x.K = &newKey;

            if (y.K != NULL) {
                //insert y into x.P;
                x.P[0] = &y;
            }
            return;
        }
        // case of overflow
        BTNode tempNode = *getBTNode(m + 1);
        //copy x to tempNode;
        tempNode.A = x.A;
        tempNode.K = x.K;
        tempNode.n = x.n;
        tempNode.P = x.P;


        y = *getBTNode(m);
        //copy first half of tempNode to x;
        x.n = ceil(tempNode.n/2);
        split(tempNode, x.n, x);
        //copy second half of tempNode to y;
        y.n = ceil(tempNode.n / 2);
        split(tempNode, y.n, y);

        //insert newKey and y into tempNode;
        insertBT(&tempNode, (y.n), newKey);

        newKey = tempNode.K[m / 2];

        delete &tempNode;
    }
    // now root has been splited
    // level of tree increases
    T = getBTNode(m);
    T->K[0] = newKey;
    T->P[0] = &x;
    T->P[1] = &y;
    T->n = 1;
}

/**
 * deleteBT deletes oldKey from T.
 * @param T: a B-tree
 * @param m: fanout of B-tree
 * @param oldKey: a key to delete
 */
void deleteBT(BTree T, int m, int oldKey)
{
    BTNode x;
    if (T)
        x = *T;
    else
        x = *getBTNode(m);

    BTNode y = *getBTNode(m);
    Stack stack;
    iStack istack;
    int i;
    BTNode internalNode;
    BTNode bestSibling = *getBTNode(m);
    BTNode parent;

    // find position to insert newKey while storing parent node on stack
    while (x.K != NULL) {
        i = binarySearch(x.K, m, oldKey);

        if ((i < x.n) && (oldKey == x.K[i]))
            return;

        stack.push(x);
        istack.push(i);

        parent = x;
        x = *x.P[i];
    }

    if (x.K == NULL)
        return;

    // if oldKey was found in internal node,
    // exchange key with successor and delete successor
    if (x.P[i + 1] != NULL) {
        internalNode = x;
        stack.push(x);
        istack.push(i + 1);
        x = *x.P[i + 1];

        while (x.K != NULL) {
            stack.push(x);
            istack.push(0);
            x = *x.P[0];
        }
    }

    // exchange key with successor
    if (x.K == NULL) {
        x = stack.pop();
        internalNode.K[i] = x.K[0];
        x.K[0] = oldKey;
        i = istack.pop();
    }

    //delete oldKey from x;
    deleteBT(&x, x.n, oldKey);

    while (!stack.isEmpty()) {
        if (x.n >= (m - 1) / 2)
            return;
        // case of underflow
        y = stack.pop();
        i = istack.pop();
        //bestSibling <- best sibling of x;
        bestSibling = *parent.P[i + 1];
        
        // case of key redistribution
        if (bestSibling.n > (m - 1) / 2) {
            //move a key from y to x;
            x.K[x.n] = y.K[i];
            //move a key from bestSibling to y;
            y.K[i] = bestSibling.K[0];
            //move a node from bestSibling to x;
            for (int j = 1; j < bestSibling.n; ++j) {
                bestSibling.K[j - 1] = bestSibling.K[j];
                bestSibling.P[j - 1] = bestSibling.P[j];
            }

            x.n += 1;
            bestSibling.n -= 1;

            break;
        }

        // case of node merge
        //move a key from y to left node between x and bestSibling;
        x.K[x.n - 1] = y.K[i];
        //merge x.K and bestSibling.K;
        //merge x.P and bestSibling.P;
        for (int j = 0; j < bestSibling.n; ++j) {
            x.K[j + x.n] = bestSibling.K[j];
            x.P[j + 1] = bestSibling.P[j];
        }
        for (int j = i + 1; j < y.n; ++j) {
            y.K[j - 1] = y.K[j];
        }
        for (int j = i + 2; j <= y.n; ++j) {
            y.P[j - 1] = y.P[j];
        }
        x.n += bestSibling.n + 1;
        y.n--;

        delete &bestSibling;
        
        x = y;
    }
    // now root has been merged
    // level of tree decreases
    if (x.n == 0) {
        T = x.P[0];
        delete &x;
    }

}

/**
 * inorderBT implements inorder traversal in T.
 * @param T: a B-tree
 */
void inorderBT(BTree T)
{
    BTNode x = *T;
    /* write your code here */
    int i = 0;
    while (T) {
        for (i; i < x.n; i++) {
            if (x.K[i] != NULL) {
                printf("%d", x.K[i]);
            }

            if (x.P[i] != NULL)
                inorderBT(x.P[i]);
        }
    }
}

int main()
{
    /* DO NOT MODIFY CODE BELOW */
    FILE* f;
    for (int m = 3; m <= 4; m++) {
        BTree T = NULL;

        f = fopen("./insertSequence.txt", "r");
        for (int n; !feof(f);) {
            fscanf(f, "%d", &n);
            insertBT(T, m, n);
            inorderBT(T);
            printf("\n");
        }
        fclose(f);
        
        f = fopen("./deleteSequence.txt", "r");
        for (int n; !feof(f);) {
            fscanf(f, "%d", &n);
            deleteBT(T, m, n);
            inorderBT(T);
            printf("\n");
        }
        fclose(f);
        
    }
}
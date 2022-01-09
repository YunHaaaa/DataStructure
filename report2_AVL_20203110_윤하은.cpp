////////////////////////////////////////////////////////////////////////
// report1 : AVL Tree
// Name: Yun Ha Eun
// ID: 20203110
////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

extern inline int max(int a, int b) { return a < b ? b : a; }
const int StackSize = 10;

typedef struct AVLNode {
	int data, height;
	int address, bf;
	struct AVLNode* left, * right;
	AVLNode(int x) : data(x), height(1), left(NULL), right(NULL), address(NULL), bf(0) {}
}AVLNode;

/**
 * getAVLNode returns a new node.
 * @return a new node
 */
AVLNode* getAVLNode()
{
	AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
	if (node) {
		node->height = 1;
		node->bf = 0;
		node->left = node->right = NULL;
	}
	return node;
}

typedef AVLNode* AVLTree;

class Stack {
private:
	AVLTree* stack;
public:
	int top = -1;
	Stack(); //top 을 -1 로 초기화 하여 스택생성
	void push(AVLTree val) { stack[++top] = val; }
	AVLTree pop() { return stack[top--]; }
	int isEmpty() { return top == -1; }
	int isFull() { return top == StackSize - 1; }
};
 
Stack::Stack() {
	stack = new AVLTree [StackSize];
	top = -1;
}


AVLNode* root = NULL;
int n = 0;
//queue<int> q;
bool find = false; 
AVLTree* p = 0;
AVLTree* q = 0;
AVLTree* x = 0;
AVLTree* f = 0;
Stack stack;
string rotationType = "NO";

/**
 * height returns the height of T.
 * @param T: an AVL tree
 * @return height of T
 */
int height(AVLTree T)
{
	if (T == NULL)
		return 0;
	return T->height;
}

AVLNode* rotateR(AVLNode* pNode) {
	AVLNode* newNode = pNode->left;
	if (newNode != NULL) {
		pNode->left = newNode->right;
		newNode->right = pNode;
		pNode->height = 1 + max(height(pNode->left), height(pNode->right));
		newNode->height = 1 + max(height(newNode->left), height(newNode->right));
		return newNode;
	}
	return pNode;
}

AVLNode* rotateL(AVLNode* pNode) {
	AVLNode* newNode = pNode->right;
	if (newNode != NULL) {
		pNode->right = newNode->left;
		newNode->left = pNode;
		pNode->height = 1 + max(height(pNode->left), height(pNode->right));
		newNode->height = 1 + max(height(newNode->left), height(newNode->right));
		return newNode;
	}
	return pNode;
}

AVLNode* rotateTree(AVLTree* T, string rotationType, AVLTree* p, AVLTree* q)
{
	if (rotationType == "L")
		return rotateL(*p);
	else //(rotationType == "R")
		return rotateR(*p);

}
AVLNode* checkBalance(AVLTree* T, int newKey, string rotationType, AVLTree* a, AVLTree* b)
{
	p = T;
	x = T;
	// update height and balancing factor while popping parent node from stack
	while (!stack.isEmpty()) {
		if (q != NULL) {
			*q = stack.pop();
			(*q)->height = 1 + max((*q)->left->height, (*q)->right->height);
			(*q)->bf = (*q)->left->height - (*q)->right->height;

			if (1 < (*q)->bf || (*q)->bf < -1) {
				if (x == NULL) {
					x = q;
					if (f)
						*f = stack.pop(); //stack.top
				}
			}
		}
	}

	// if there's no problem, return
	if (x == NULL) {
		rotationType = "NO";
		p = NULL;
		q = NULL;
	}

	// rebalance tree
	else if (1 < (*x)->bf) {
		if ((*x)->data < (*p)->left->data) {
			rotationType = "R";
		}
		else {
			(*p)->left = rotateL((*p)->left);
			rotationType = "R";
		}
	}
	else {
		if ((*x)->data > (*p)->right->data) {
			rotationType = "L";
		}
		else {
			(*p)->right = rotateR((*p)->right);
			rotationType = "L";
		}
	}
	return rotateTree(T, rotationType, p, q);
}



/**
 * insertAVL inserts newKey into T.
 * @param T: an AVL tree
 * @param newKey: a key to insert
 */
void insertBST(AVLTree* T, int newKey)
{
	p = T;

	// find position to insert newKey while storing parent node on stack
	while (*p != NULL) {
		if (newKey == (*p)->data)
			return;
		q = p;
		stack.push(*q);

		if (newKey < (*p)->data)
			*p = (*p)->left;
		else
			*p = (*p)->right;
	}

	// create new node
	AVLTree y = getAVLNode();
	y->data = newKey;

	// insert y as a child of q
	if (T == NULL)
		T = &y;
	else if (newKey < (*q)->data)
		(*q)->left = y;
	else
		(*q)->right = y;

	checkBalance(T, newKey, rotationType, p, q);
}

/**
 * deleteAVL deletes deleteKey from T.
 * @param T: an AVL tree
 * @param deleteKey: a key to delete
 */
void deleteBST(AVLTree* T, int deleteKey)
{
	p = T;
	// perform standard BST deletion
    // find position of deleteKey while storing parent node on stack
	while (p != NULL and deleteKey != (*p)->data) {
		q = p;
		stack.push(*q);
		if (deleteKey < (*p)->data)
			*p = (*p)->left;
		else
			*p = (*p)->right;
	}

	if (p == NULL)
		return;  // deleteKey was not found

	// case of degree 2 is reduced to case of degree 0 or case of degree 1
	if ((*p)->left != NULL && (*p)->right != NULL) {
		stack.push(*p);
		AVLTree* tempNode = p;

		if ((*p)->left->height <= (*p)->right->height) {
			*p = (*p)->right;
			while ((*p)->left != NULL) {
				stack.push(*p);
				*p = (*p)->left;
			}
		}

		else {
			*p = (*p)->left;
			while ((*p)->right != NULL) {
				stack.push(*p);
				*p = (*p)->right;
			}
		}
		(*tempNode)->data = (*p)->data;
		if (q)
			*q = stack.pop(); //stack.top
	}


	// now degree of p is 0 or 1
	// delete p from T
	if (p) {
		if ((*p)->left == NULL && (*p)->right == NULL) {  // case of degree 0
			if (q == NULL)
				T = NULL; // case of root
			else if ((*q)->left == *p)
				(*q)->left = NULL;
			else
				(*q)->right = NULL;
		}
		else { // case of degree 1
			if ((*p)->left != NULL) {
				if (q == NULL)
					*T = (*T)->left; // case of root
				else {
					if ((*q)->left == *p)
						(*q)->left = (*p)->left;
					else
						(*q)->right = (*p)->left;
				}
			}
			else {
				if (q == NULL)
					*T = (*T)->right; // case of root
				else if ((*q)->left == *p)
					(*q)->left = (*p)->right;
				else
					(*q)->right = (*p)->right;
			}
		}
	}
	delete p;

	checkBalance(T, deleteKey, rotationType, T, q);
}

/**
 * inorderAVL implements inorder traversal in T.
 * @param T: an AVL tree
 */
void inorderAVL(AVLTree T)
{
	if (T != NULL) {
		inorderAVL(T->left);
		cout << T->data << " ";
		//if (node->right != NULL)
		inorderAVL(T->right);
	}
}

int main()
{
	/* DO NOT MODIFY CODE BELOW */
	int testCases[] = { 40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 66, 10, 22, 30, 44, 55, 50, 60, 25, 49 };

	AVLTree T = NULL;

	for (int i = 0; i < 20; i++)
	{
		insertBST(&T, testCases[i]);
		inorderAVL(T);
		printf("\n");
	}
	for (int i = 0; i < 20; i++)
	{
		deleteBST(&T, testCases[i]);
		inorderAVL(T);
		printf("\n");
	}
	for (int i = 0; i < 20; i++)
	{
		insertBST(&T, testCases[i]);
		inorderAVL(T);
		printf("\n");
	}
	for (int i = 19; 0 <= i; i--)
	{
		deleteBST(&T, testCases[i]);
		inorderAVL(T);
		printf("\n");
	}
}
////////////////////////////////////////////////////////////////////////
// report1 : Binary Search Tree
// Name: Yun Ha Eun
// ID: 20203110
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
using namespace std;
template <class T> class Tree;

template <class T>
class Node {
private:
	T data;
	Node<T>* left; // left link
	Node<T>* right; // right link
	int Height;
public:
	~Node<T>() {};
	Node<T>(T value) : data(value), left(0), right(0), Height(0) {}// = value; leftchild = 0; rightchild = 0; }
	friend class Tree<T>;
};

template <class T>
class Stack {
private:
	int top;
	Node<T>* stack;
public:
	int size;
	Stack(int sz = 0);
	~Stack();
	void push(Node<T>* node);
	T pop();
	int isEmpty() { return top == -1; }
	int isFull() { return top == size - 1; }
	friend class Tree<T>;
};

template <class T>
class Tree {
public:
	Node<T>* root;
	Stack<T> stack;// (int size);
	Tree() { this->root = NULL; }
	~Tree();
	void searchBST(Node<T>* n, T searchKey);
	void inorderBST(Node<T>* n);
	Node<T>* insertBST(Node<T>* n, T searchKey);
	Node<T>* deleteBST(Node<T>* n, T searchKey);
	void Operand(Node<T>* n);
	void Operator(Node<T>* n);
	int height(Node<T>* node);
	int noNodes(Node<T>* node);
	Node<T>* maxNode(Node<T>* p);
	Node<T>* minNode(Node<T>* p);
	Node<T>* getNode(T searchKey);
	void drawTree() { drawBSTree(root, 1); }
	void drawBSTree(Node<T>* P, int level);
private:
	void deleteMemory(Node<T>* n);
	friend class Stack<T>;
};

template <class T>
Stack<T>::Stack(int sz) {
	stack = new Node<T>*[sz];
//	assert(stack != 0);
	top = -1;
	size = sz;
}

template <class T>
Stack<T>::~Stack()
{
	delete stack;
}

template <class T>
void Stack<T>::push(Node<T>* node) {
	if (isFull()) {
		cerr << "Error: push on full stack" << endl;
		exit(-1);
	}
	stack[++top] = node;
}

template <class T>
T Stack<T>::pop() {
	if (isEmpty()) {
		cerr << "Error: pop on empty stack" << endl;
		exit(-1);
	}
	return stack[top--];
}

template <class T>
void Tree<T>::searchBST(Node<T>* n, T searchKey) {
	if (n == NULL) return NULL; //search unsuccessful
	else {
		if (searchKey == n->data) return n;
		else if (searchKey < n->data)
			n = search(n->left, searchKey); //search left subtree
		else if (searchKey > n->data)
			n = search(n->right, searchKey); //search right subtree
	}
	return n;
}

template <class T>
Node<T>* Tree<T>::insertBST(Node<T>* N, T newKey) {
	size++;
	Node<T>* n = N;
	Node<T>* q = NULL;

	if (n == NULL) { // if empty
		getNode(newKey);
	}
	else if (newKey == n->data) {
		q = n;
		stack.push(q);
		return n;
	}
	else if (newKey < n->data)
		n->left = insertBST(n->left, newKey);
	else// if (newKey > n->data)
		n->right = insertBST(n->right, newKey);


	// update height while popping parent node from stack
	while (!stack.isEmpty()) {
		q = stack.pop();
		q->Height = 1 + max(height(q->left), height(q->right));
	}
	return n;
}


template <class T>
Node<T>* Tree<T>::deleteBST(Node<T>* N, T searchKey) {
	Node<T>* n = N;
	Node<T>* q = NULL;
	Node<T>* temp;
	string flag = "";

	// find position of deleteKey while storing parent node on stack
	while (n != NULL && n->data != searchKey) {
		q = n;
		stack.push(q);
		if (searchKey < n->data)
			n->left = deleteBST(n->left, searchKey); /* move to the node */
		else //(searchKey > n->data)
			n->right = deleteBST(n->right, searchKey); /* arrived at the node*/
	}
	if (n == NULL) {
		printf("Not found");
		return n;
	}

	// case of degree 2 is reduced to case of degree 0 or case of degree 1
	if (n->left != NULL and n->right != NULL) {
		temp = n;
		stack.push(n);
		if (height(n->left) > height(n->right)) {
			temp = maxNode(n->left); flag = "LEFT";
		}
		else if (height(n->left) < height(n->right)) {
			temp = minNode(n->right); flag = "RIGHT";
		}
		else if (height(n->left) == height(n->right)) {
			if (noNodes(n->left) >= noNodes(n->right)) {
				temp = maxNode(n->left); flag = "LEFT";
			}
			else { //noNodes(n.left) < noNodes(n.right) :

				temp = minNode(n->right); flag = "RIGHT";
			}
		}			
		

		/*if (noNodes(n->left) <= noNodes(n->right)) {
			n = n->right;
			while (n->left != NULL) {
				stack.push(n);
				n = n->left;
			}
		}
		else {
			n = n->left;
			while (n->right != NULL) {
				stack.push(n);
				n = n->right;
			}
		}*/

		n->data = temp->data;
		if (flag == "LEFT")
			deleteBST(n->left, temp->data);
		else
			deleteBST(n->right, temp->data);
		q = stack.pop; //stack.top
	}

	// now degree of p is 0 or 1
	// delete p from T

	if ((n->left == NULL) && (n->right == NULL)) {
		if (q == NULL)
			root = root.left; // case of root
		else if (q->left = n)
			q->left = n->left;
		else
			q->right = n->left;
	}
	else {
		if (q == NULL)
			root = root.right;
		else if (q->left = n)
			q->left = n->right;
		else
			q->right = n->right;
	}
	delete n;

	// update height while popping parent node from stack
	while (!stack.isEmpty()) {
		q = stack.pop();
		q->Height = 1 + max(height(q->left), height(q->right));
	}
	return n;
}

template<class T>
Node<T>* Tree<T>::getNode(T searchKey)
{
	Node<T>* n = new Node<T>(searchKey);
	n->left = NULL;
	n->right = NULL;
	return n;
}

template<class T>
int Tree<T>::height(Node<T>* node)
{
	return node->Height;
}

template<class T>
int Tree<T>::noNodes(Node<T>* node)
{
	return size;
}

template<class T>
Node<T>*Tree<T>::maxNode(Node<T>* p)
{
	if (p == NULL) return NULL;
	else if (p->right == NULL) return p;
	else return findMax(p->right);
}

template<class T>
Node<T>* Tree<T>::minNode(Node<T>* p)
{
	if (p == NULL) return NULL;
	if (p->left == NULL) return p;
	else return find_min(p->left);
}


template <class T>
Tree<T>::~Tree()
{
	deleteMemory(root);
	//this->root = NULL;
}

template <class T>
void Tree<T>::deleteMemory(Node<T>* node)
{
	if (node->left != NULL)
		deleteMemory(node->left);
	if (node->right != NULL)
		deleteMemory(node->right);
	delete node;
}


template <class T>
void Tree<T>::Operand(Node<T>* node)
{
	if (this->root == NULL) {
		root = node;
		return;
	}
	Node<T>* p = root;
	while (p->right != NULL)
		p = p->right;
	p->right = node;
}


template <class T>
void Tree<T>::inorderBST(Node<T>* node)
{
	if (node != NULL) {
		inorderBST(node->left);
		cout << node->data << " ";
		//if (node->right != NULL)
		inorderBST(node->right);
	}
}

template <class T>
void Tree<T>::drawBSTree(Node<T>* p, int level)
{
	if (p != 0 && level <= 7) {
		drawBSTree(p->right, level + 1);
		for (int i = 1; i <= (level - 1); i++)
			cout << " ";
		cout << p->data;
		if (p->left != 0 && p->right != 0) cout << " <" << endl;
		else if (p->right != 0) cout << " /" << endl;
		else if (p->left != 0) cout << " \\" << endl;
		else cout << endl;
		drawBSTree(p->left, level + 1);
	}
}

int main() {
	Tree<int> T;

	// ª¿‘
	T.insertBST(T.root, 25); T.inorderBST(T.root);
	T.insertBST(T.root, 500); T.inorderBST(T.root);

	T.insertBST(T.root, 100); T.inorderBST(T.root);
	T.insertBST(T.root, 999); T.inorderBST(T.root);
	// ªË¡¶ 1
	T.deleteBST(T.root, 25); T.inorderBST(T.root);
	T.deleteBST(T.root, 500); T.inorderBST(T.root);
	
	T.deleteBST(T.root, 100); T.inorderBST(T.root);
	T.deleteBST(T.root, 999); T.inorderBST(T.root);

	// ¿Áª¿‘
	T.insertBST(T.root, 25); T.inorderBST(T.root);
	T.insertBST(T.root, 500); T.inorderBST(T.root);
	
	T.insertBST(T.root, 100); T.inorderBST(T.root);
	T.insertBST(T.root, 999); T.inorderBST(T.root);
	// ªË¡¶ 2
	T.deleteBST(T.root, 999); T.inorderBST(T.root);
	T.deleteBST(T.root, 100); T.inorderBST(T.root);
	
	T.deleteBST(T.root, 500); T.inorderBST(T.root);
	T.deleteBST(T.root, 25); T.inorderBST(T.root);
	
	T.~Tree();
	exit(1);
	return 0;
}

////////////////////////////////////////////////////////////////////////
// lab8 : Tree Build, Traverse & Evaluation
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
	int prio; // priority number from precedence table
public:
	~Node<T>() {};
	Node<T>(T value) : data(value), prio(4), left(0), right(0) {}// = value; leftchild = 0; rightchild = 0; prio = }
	friend class Tree<T>;
};

template <class T>
class Tree {
public:
	Node<T>* root;
	Tree() { this->root = NULL; }
	~Tree();
	void searchBST(Node<T>* n, int searchKey);
	void inorderBST(Node<T>* n);
	void insertBST(Node<T>* n, int searchKey);
	void deleteBST(Node<T>* n, int searchKey);
	void Operand(Node<T>* n);
	void Operator(Node<T>* n);
	void height(T);
	void noNodes(T);
	Node* maxNode(Node<T>* p);
	Node* minNode(Node<T>* p);
	Node* getNode();
	void Tree::drawTree() { drawBSTree(root, 1); }
	void drawBSTree(Node<T>* P, int level);
private:
	void deleteMemory(Node<T>* n);
};

template <class T>
void Tree<T>::searchBST(Node<T>* n, int searchKey) {
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


int level = 0;

template <class T>
void Tree<T>::insertBST(Node<T>* n, int searchKey) {
	level++;
	if (n = NULL) { // if empty
		create new_node(n);
		n->data = searchKey;
		n->left = NULL;
		n->right = NULL;
	}
	else if (searchKey < n->data)
		n->left = INSERT(n->left, searchKey);
	else if(searchKey > n->data)
		n->right = INSERT(n->right, searchKey);

	return n;
}

template <class T>
void Tree<T>::deleteBST(Node<T>* n, int searchKey) {
	if (n != NULL) {
		if (searchKey < n->data)
			n->left = delete(searchKey, n->left) /* move to the node */
		else if (searchKey > n->data)
			n->right = delete (searchKey, n->right) /* arrived at the node*/
		else if ((n->left == NULL) && (n->right == NULL))
			n = NULL /*leaf*/
		else if (n->left == NULL) {
			p = n; n = n->right; delete(p); / rightchild only * /
		}
		elseif(n->right == NULL) {
			p = n; n = n->left; delete(p); /*left child only */
		}
		else temp = find_min(n->right) /*both child exists */
			n->data = temp->data;
		n->right = delete(n->right, n->data);
	}
	else print("Not found"); 5
		return n;
}

template<class T>
Node* Tree<T>::getNode()
{
}

template<class T>
void Tree<T>::height(T)
{
}

template<class T>
void Tree<T>::noNodes(T)
{
}

template<class T>
Node *Tree<T>::maxNode(Node<T>* p)
{
	if (p == NULL) return NULL;
	else if (p->right == NULL) return p;
	else return findMax(p->right);
}

template<class T>
Node *Tree<T>::minNode(Node* p)
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
void Tree<T>::Operator(Node<T>* node)
{
	if (root->prio >= node->prio) {
		node->left = root;
		root = node;
	}
	else {
		node->left = root->right;
		root->right = node;
	}
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
	
	insertBST(T, 25); inorderBST(T);
	insertBST(T, 500); inorderBST(T);
	
	insertBST(T, 100); inorderBST(T)
	insertBST(T, 999); inorderBST(T);
	// ªË¡¶ 1
	deleteBST(T, 25); inorderBST(T);
	deleteBST(T, 500); inorderBST(T);
	
	deleteBST(T, 100); inorderBST(T);
	deleteBST(T, 999); inorderBST(T);

	T.~Tree();
	exit(1);
	return 0;
}

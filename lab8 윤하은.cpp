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
	void build(string exp);
	void inorder(Node<T>* n);
	void insert(T data);
	void postorder(Node<T>* n);
	void preorder(Node<T>* n);
	void Operand(Node<T>* n);
	void Operator(Node<T>* n);
	int evalTree(Node<T>* n);
	void print(Node<T>* P, int level);
private:
	void deleteMemory(Node<T>* n);
};

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

int level = 0;
static char prec[4][2] = { '*', 2, '/', 2, '+', 1, '-', 1 };

template <class T>
void Tree<T>::build(string exp)
{
	int i = 0;
	while (exp[i] != NULL)
	{
		insert(exp[i]);
		i++;
	}
	level = i;
}

template <class T>
void Tree<T>::insert(T data) {
	int r = 0;
	int i = 0;
	Node<T>* node  = new Node<T>(data);
	for (i = 0; i < 4; ++i) {
		if (node->data == prec[i][0]) {
			node->prio = prec[i][1];
			break;
		}
	}
	if (i == 4) 
		Operand(node);
	else 
		Operator(node);
}

template <class T>
void Tree<T>::Operand(Node<T>* node)
{
	if (this->root == NULL) {
		root = node;
		return;
	}
	Node<T>* p = root;
	while(p->right != NULL) 
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
void Tree<T>::inorder(Node<T>* node)
{
	if (node->left != NULL) 
		inorder(node->left);
	cout << node->data << " ";
	if (node->right != NULL)
		inorder(node->right);
}

template <class T>
int Tree<T>::evalTree(Node<T>* node)
{
	int value = 0;
	int left, right;
	if (node != NULL) {
		if (node->data >= '0' && node->data <= '9')
			value = node->data - '0';
		else {
			left = evalTree(node->left);
			right = evalTree(node->right);
			switch ((char)node->data){
				case '+': value = left + right; break;
				case '-': value = left - right; break;
				case '*': value = left * right; break;
				case '/': value = left / right;	break;
			}
		}// endif
		// cout << "Empty Tree" << endl;
	}
	return value;
}

template <class T>
void Tree<T>::print(Node<T>* P, int level)
{
	int j = 1;
	if (P != NULL) {
		print(P->right, level + 1); //Space over (skip levels)
		while (j++ < level) cout << "    "; // Print data
		cout << P->data;
		if (P->left != 0 && P->right != 0) cout << " <"; //two child
		else if (P->right != 0) cout << "   /"; //only right child
		else if (P->left != 0) cout << "   \\"; //only left child
		cout << endl;
		print(P->left, level + 1);
	}
}

template <class T>
void Tree<T>::postorder(Node<T>* node) {
	if (node->left != NULL)
		postorder(node->left);
	if (node->right != NULL)
		postorder(node->right);
	cout << node->data << " ";
}

template <class T>
void Tree<T>::preorder(Node<T>* node) {
	cout << node->data << " ";
	if (node->left != NULL) {
		preorder(node->left);
	}
	if (node->right != NULL) {
		preorder(node->right);
	}
}

int main() {
	Tree<char> t1;
	string exp = "8+9-2*3";
	string exp1 = "A/B*C*D+E";

	cout << endl << "1. Infix Expression1 : " << exp << endl;
	t1.build(exp);
	cout << endl << "InOrder : ";
	t1.inorder(t1.root);
	cout << endl << "PostOrder : ";
	t1.postorder(t1.root);
	cout << endl << "PreOrder : ";
	t1.preorder(t1.root);
	cout << endl << "Evaluation : " << t1.evalTree(t1.root) << endl;
	t1.print(t1.root, level);
	cout << endl << endl;
		
	t1.root = NULL;
	cout << "2. Infix Expession2 : " << exp1 << endl;
	t1.build(exp1);
	cout << endl << "InOrder : ";
	t1.inorder(t1.root);
	cout << endl << "PostOrder : ";
	t1.postorder(t1.root);
	cout << endl << "PreOrder : ";
	t1.preorder(t1.root);
	cout << endl;
	t1.print(t1.root, level);
	cout << endl << endl;

	t1.~Tree();
	exit(1);
	return 0;
}
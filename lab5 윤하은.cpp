////////////////////////////////////////////////////////////////////////
// lab5: postfic conversion
// Name: Yun Ha Eun
// ID: 20203110
/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
using namespace std;

#define max 80
#define MAX_SIZE 5

char stack[max];
int top, nch;
char ch;

char line[max];
char buffer[max];

void posteval(char buffer[]);
void postconv(char buffer1[]);

void push(char data) { stack[++top] = data; }
void npush(int ndata) {	stack[++top] = ndata; }

void stackcreate() { top = 0; }

char pop() { ch = stack[top--]; return ch; }
int npop() { nch = stack[top--]; return nch; }

int isEmpty();
int Prec(char op);
char token;

int main() {
	ifstream infile;
	char buffer1[80];
	infile.open("lab5.txt", ios::in);
	if (infile.fail()) { cout << "can't open the input file" << endl; exit(1); }

	while (infile.getline(buffer1, 80)) {
		cout << "Infix expression : " << buffer1;
		stackcreate();
		cout << "The Postfix conversion : ";
		postconv(buffer1);
		posteval(buffer);
	}
	cout << endl;
	return 0;
}

int isEmpty() {
	if (top == -1) return 1;
	else return 0;
}

void postconv(char buffer1[]) {
	char n2;
	int i = 0;
	int j = 0;

	while ((token = buffer1[i]) != '\0') {
		if (((token >= '0') && (token <= '9')) || ((token >= 'a') && (token <= 'z'))) {
			cout << token;
			buffer[j++] = token;
		}
		else if (token == '(')
			push(token);
		else if (token == ')') {
			while (stack[top] != '(') {
				n2 = pop();
				printf("%c", n2);
				buffer[j++] = n2;
			}
			n2 = pop();
		}
		else {
			while (Prec(token) <= Prec(stack[top])) {
				n2 = pop();
				cout << n2;
				buffer[j++] = n2;
			}
			push(token);
		}
		i++;
	}

	while (top != 0) {
		n2 = pop();
		cout << n2;
		buffer[j++] = n2;
	}
	cout << endl;
	buffer[j++] = '\0';
}

void posteval(char buffer[]) {
	stackcreate();
	int i = 0;
	int pn1, pn2, pn3, result;

	while (buffer[i] != '\0') {
		if (buffer[i] >= '0' && buffer[i] <= '9') {
			pn3 = buffer[i] - '0';
			npush(pn3);
			i++;
		}
		else {
			pn2 = npop();
			pn1 = npop();
			switch (buffer[i]) {
			case '+':
				result = pn1 + pn2;
				break;
			case '-':
				result = pn1 - pn2;
				break;
			case '*':
				result = pn1 * pn2;
				break;
			case '/':
				result = pn1 / pn2;
				break;
			default:
				printf("ERROR in expression\n");
				break;
			}
			i++;
			npush(result);
		}
	}
	pn3 = npop();
	cout << endl << "The final result : " << pn3 << endl << endl;
}

int Prec(char op)
{
	switch (op) {
	case '(':
	case ')':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	}
	return -1;
}

////////////////////////////////////////////////////////////////////////
// HW2:Parentheses Checker
// Name: Yun Ha Eun
// ID: 20203110
// Algorithm
// - Open data file(hw2.txt)
// - distinguish whether or not the parentheses are balanced in the expression
// - Printout the result
/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
using namespace std;

#define max 80 // define stack size

bool PChecker(char buffer[]); 
int balanced = 0, unbalanced = 0, mismatched = 0;

char stack[max];
int top;
char ch;
int match(char a, char b); 

void push(char data) { stack[++top] = data; }
char pop() { ch = stack[top--]; return ch; }
void createStack() {top = 0; }

int isEmpty() { // check whether a stack is empty or not
	if (top <= 0) return 1;
	else {
		return 0;
	}
}

int main() {
	cout << "<< HW2 : Balanced Parentheses >>" << endl << endl;

	ifstream infile;
	bool validity;
	char buffer[80];

	infile.open("hw2.txt", ios::in); // check file open error
	if (infile.fail()) { cout << "can't open the input file\n" << endl; exit(1); }

	while (infile.getline(buffer, 80)) { // check line by line
		cout << "Input Data " << buffer << endl;
		createStack();

		validity = PChecker(buffer);
		if (validity) {
			printf("The Expression is Valid\n\n");
		}	
		else
			printf("The Expression is Invalid\n\n");
	}
	// print total Number of Each Parentheses - balanced, unbalanced, mismatched
	printf("Total : Balanced : %d, Unbalanced : %d, Mismatched : %d\n", balanced, unbalanced, mismatched);
	cout << endl;
	return 0;
}

////////////////////////////////////////////////////////////////
// << PChecker(buffer) >>
// function : Check Parentheses
// buffer에 괄호가 나오면 stack을 이용해 개수와 종류가 맞는지 판별하는 함수
// - balanced, unbalanced, mismatched를 구분해 개수를 세고 boolean값을 return
////////////////////////////////////////////////////////////////

bool PChecker(char buffer[]) {
	for (int i = 0; i <= strlen(buffer) - 1; i++) {
		if (buffer[i] == '(' || buffer[i] == '{' || buffer[i] == '[')
			push(buffer[i]);
		if (buffer[i] == ')' || buffer[i] == '}' || buffer[i] == ']') {
			if (isEmpty()) { // invalid - Parentheses의 개수가 틀린 경우
				printf("The Expression has unbalanxed parentheses\n");
				unbalanced++;
				return false;
			}
			else {
				char temp = pop();
				if (!match(temp, buffer[i])) { // invalid - Parentheses의 종류가 틀린 경우
					printf("Mismatched Parenthes in the Expession are %c and %c\n", temp, buffer[i]);
					mismatched++;
					return false;
				}
			}
		}
	}

	if (isEmpty()) {// valid
		balanced++;
		return true;
	}
	else { // invalid - Parentheses의 개수가 틀린 경우
		printf("The Expression has unbalanxed parentheses\n");
		unbalanced++;
		return false;
	}
}

////////////////////////////////////////////////////////////////
// << match(a, b) >>
// function : Determine if a and b are the correct pair
// { }, [ ], ( ) : correct - return true
// else : incorrect - return false
////////////////////////////////////////////////////////////////

int match(char a, char b) {
	if (a == '[' && b == ']')
		return true;
	else if (a == '{' && b == '}')
		return true;
	else if (a == '(' && b == ')')
		return true;
	return false;
}
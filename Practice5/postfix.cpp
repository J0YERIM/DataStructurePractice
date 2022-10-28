#include <iostream>
#include <stdio.h>

// infix -> postfix
// isp >= icp인 동안 stack delete -> isp < icp일 때 입력 연산자를 stack에 저장
// 과로가 있는 수식 처리에 주의
/*
'(' : icp는 최고 -> 무조건 stack에 저장
		isp는 최저 -> 다음의 연산자 무조건 stack에 저장
')' 이 입력에 나타나면 대응하는 '('까지 stack delete
*/

class StackInt {
	int* arr;
	int top;
	int capacity;
public:
	StackInt();
	~StackInt();

	int* getArr() { return arr; }
	int getTop() { return top; }
	int getCapacity() { return capacity; }

	void push(int);
	int pop();

	bool isEmpty();
	bool isFull();
	void stackFull();

	void printStack();
};

StackInt::StackInt() {
	arr = new int[10];
	capacity = 10;
	top = -1;
}

StackInt::~StackInt() {
	delete[] arr;
}

void StackInt::push(int item) {
	if (isFull()) stackFull();
	arr[++top] = item;
}

int StackInt::pop() {
	if (isEmpty()) {
		return -1;
	}
	return arr[top--];
}

bool StackInt::isEmpty() {
	return top == -1;
}

bool StackInt::isFull() {
	return top == capacity - 1;
}

void StackInt::stackFull() {
	int* newArr = new int[capacity * 2];
	std::copy(arr, arr + capacity, newArr);
	delete[] arr;
	capacity *= 2;
	arr = newArr;
	newArr = NULL;
	printf("stack의 사이즈를 늘렸습니다.\n");
}

void StackInt::printStack() {
	if (!isEmpty()) {
		for (int i = 0; i <= getTop(); i++)
			printf("%d ", getArr()[i]);
	}
}

class StackChar {
	char* arr;
	int top;
	int capacity;
public:
	StackChar();
	~StackChar();

	char* getArr() { return arr; }
	int getTop() { return top; }
	int getCapacity() { return capacity; }
	char getTopValue() { return arr[top]; }

	void push(char);
	char pop();

	bool isEmpty();
	bool isFull();
	void stackFull();
	void printStack();
};

StackChar::StackChar() {
	arr = new char[10];
	capacity = 10;
	top = -1;
}

StackChar::~StackChar() {
	delete[] arr;
}

void StackChar::push(char item) {
	if (isFull()) stackFull();
	arr[++top] = item;
}

char StackChar::pop() {
	if (isEmpty()) {
		return -1;
	}
	return arr[top--];
}

bool StackChar::isEmpty() {
	return top == -1;
}

bool StackChar::isFull() {
	return top == capacity - 1;
}

void StackChar::stackFull() {
	char* newArr = new char[capacity * 2];
	std::copy(arr, arr + capacity, newArr);
	delete[] arr;
	capacity *= 2;
	arr = newArr;
	newArr = NULL;
	printf("stack의 사이즈를 늘렸습니다.\n");
}

void StackChar::printStack() {
	if (!isEmpty()) {
		for (int i = 0; i <= getTop(); i++)
			printf("%c ", getArr()[i]);
	}
}

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;
StackInt stkInt;
StackChar stkChar;
/* isp와 icp 배열 -- 인덱스는 연산자 
lparen, rparen, plus, minus, times, divide, mod, eos의 우선순위 값*/
int isp[] = { 0,19,12,12,13,13,13,0 };
int icp[] = { 20,19,12,12,13,13,13,0 };

int eval(char* expr); // 후위 표기식을 연산하는 함수
precedence getToken(char* expr, char* symbol, int* n); // 수식 문자열에서 다음 문자를 검사하여 해당 token을 반환
void postfix(char* expr, char* new_expr); // 수식 변환 프로그램 (infix -> postfix)
char printToken(precedence token);
precedence printToken2(char c);

int main() {
	char expr[] = "((((6/2)-3+(4*2))-5*3))";
	char new_expr[100] = "";
	printf("Infix : %s\n", expr);
	printf("Infix to Postfix : \n");
	postfix(expr, new_expr);
	printf("Postfix: %s\n", new_expr);
}

precedence getToken(char* expr, char* symbol, int* n) {
	// 수식 문자열에서 다음 문자를 검사하여 해당 token을 반환
	*symbol = expr[(*n)++]; // expr 수식 문자열의 n번째 인덱스를 symbol 내부값으로 삽입
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand; // 에러 검사는 하지 않고 기본 값은 피연산자
	}
}

void postfix(char* expr, char* new_expr) {
	// 수식 변환 프로그램 (infix -> postfix)
	char symbol;
	precedence token;
	char tmp;
	int n = 0, i = 0; // n : 수식 문자열의 현재 판독 위치 i : new_expr를 가리키는 인덱스
	stkChar.push('\0'); // eos를 스택에 삽입

	printf("Token | Stack       | Top | Output\n");

	for (token = getToken(expr, &symbol, &n); token != eos; token = getToken(expr, &symbol, &n)) {
		// eos일 때까지 입력 받기
		if (token == operand) new_expr[i++] = symbol; // 피연산자일 경우 new_expr에 저장
		else if (token == rparen) {
			// 왼쪽 괄호가 나올 때까지 토큰들을 제거해서 출력시킴
			while (stkChar.getTopValue() != '(') // new_expr에 저장
				new_expr[i++] = stkChar.pop();
			stkChar.pop(); // 왼쪽 괄호를 버린다.
			continue;
		}
		else { // 우선순위가 높은 연산자
			/* symbol의 isp가 token의 icp보다 크거나 같으면
			symbol을 제거하고 출력시킴 */
			while (isp[printToken2(stkChar.getTopValue())] >= icp[token])
				new_expr[i++] = stkChar.pop(); // new_expr에 저장
			stkChar.push(printToken(token));
		}
		printf("%c | ", symbol);
		stkChar.printStack();
		printf(" | %8d | ", stkChar.getTop());
		printf("%8s\n", new_expr);
	}
	while ((tmp = stkChar.pop()) != '\0')
		new_expr[i++] = tmp;
	new_expr[i] = '\0';
	printf("%c | ", symbol);
	stkChar.printStack();
	printf(" | %8d | ", stkChar.getTop());
	printf("%8s\n", new_expr);
}

char printToken(precedence token) {
	char temp[] = { '(', ')', '+', '-', '*', '/', '%' };
	return temp[token];
}

precedence printToken2(char c) {
	switch (c) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand; // 에러 검사는 하지 않고 기본 값은 피연산자
	}
}
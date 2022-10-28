#include <iostream>
#include <stdio.h>

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

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;
StackInt stkInt;

int eval(char* expr); // 후위 표기식을 연산하는 함수
precedence getToken(char* expr, char* symbol, int* n); // 수식 문자열에서 다음 문자를 검사하여 해당 token을 반환

int main() {
	char expr[] = "62/3-42*+53*-";
	printf("Postfix : %s\n", expr);
	printf("Eval %d\n", eval(expr));
}

int eval(char* expr) { // 후위 표기식을 연산하는 함수
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0; // 수식 문자열의 현재 판독 위치

	printf("Token | Stack     | Top\n");
	token = getToken(expr, &symbol, &n);
	while (token != eos) {
		if (token == operand) { // 피연산자를 만나면
			stkInt.push(symbol - '0'); // 스택 삽입
		}
		else {
			/*
			stakc에서 피연산자 2개를 삭제한 후
			이를 이용하여 수식을 계산한 후 결과를 다시 stack에 저장
			*/
			op2 = stkInt.pop();
			op1 = stkInt.pop();
			switch (token) {
			case plus:
				stkInt.push(op1 + op2);
				break;
			case minus:
				stkInt.push(op1 - op2);
				break;
			case times:
				stkInt.push(op1 * op2);
				break;
			case divide:
				stkInt.push(op1 / op2);
				break;
			case mod:
				stkInt.push(op1 % op2);
				break;
			}
		}
		printf("%c | ", symbol);
		stkInt.printStack();
		printf("       | %d\n", stkInt.getTop());
		token = getToken(expr, &symbol, &n);
	}
	return stkInt.pop(); // return result
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
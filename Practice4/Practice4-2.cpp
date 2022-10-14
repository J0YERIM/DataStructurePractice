#include <iostream>
#define SIZE 1000
using namespace std;

class Stack {
	int* arr;
	int top;
	int capacity;
public:
	Stack();
	~Stack();

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

Stack::Stack() {
	arr = new int[10];
	capacity = 10;
	top = -1;
}

Stack::~Stack() {
	delete[] arr;
}

void Stack::push(int item) {
	if (isFull()) stackFull();
	arr[++top] = item;
}

int Stack::pop() {
	if (isEmpty()) {
		cout << "Stack이 비어있습니다.\n";
		return -1;
	}
	return arr[top--];
}

bool Stack::isEmpty() {
	return top == -1;
}

bool Stack::isFull() {
	return top == capacity - 1;
}

void Stack::stackFull() {
	int* newArr = new int[capacity * 2];
	copy(arr, arr + capacity, newArr);
	delete[] arr;
	capacity *= 2;
	arr = newArr;
	newArr = NULL;
	cout << "stack의 사이즈를 늘렸습니다.\n";
}

void Stack::printStack() {
	cout << "\nindex : item\n";
	if (!isEmpty()) {
		for (int i = 0; i <= getTop(); i++)
			cout << i << " : " << getArr()[i] << endl;
	}
}

class Queue {
	int* arr;
	int front;
	int rear;
	int capacity;
public:
	Queue();
	~Queue();

	int* getArr() { return arr; }
	int getFront() { return front; }
	int getRear() { return rear; }
	int getCapacity() { return capacity; }

	void enqueue(int);
	int dequeue();

	bool isEmpty();
	bool isFull();
	void queueFull();
	void printQueue();
};

Queue::Queue() {
	arr = new int[10];
	capacity = 10;
	front = -1, rear = -1;
}

Queue::~Queue() {
	delete[] arr;
}

void Queue::enqueue(int item) {
	if (isFull()) queueFull();
	arr[++rear] = item;
}

int Queue::dequeue() {
	if (isEmpty()) {
		cout << "queue이 비어있습니다.\n";
		return -1;
	}
	return arr[++front];
}

bool Queue::isEmpty() {
	return front == rear;
}

bool Queue::isFull() {
	return rear == capacity - 1;
}

void Queue::queueFull() {
	int* newArr = new int[capacity * 2];
	copy(arr, arr + capacity, newArr);
	delete[] arr;
	capacity *= 2;
	arr = newArr;
	newArr = NULL;
	cout << "queue의 사이즈를 늘렸습니다.\n";
}

void Queue::printQueue() {
	cout << "\nindex : item\n";
	if (!isEmpty()) {
		for (int i = getFront() + 1; i <= getRear(); i++)
			cout << i << " : " << getArr()[i] << endl;
	}
}

class Cqueue {
	int* arr;
	int front;
	int rear;
	int capacity;
public:
	Cqueue();
	~Cqueue();

	int* getArr() { return arr; }
	int getFront() { return front; }
	int getRear() { return rear; }
	int getCapacity() { return capacity; }

	void enqueue(int);
	int dequeue();

	bool isEmpty();
	bool isFull();
	void cqueueFull();
	void myCopy(int*, int*, int*);
	void printCqueue();
};

Cqueue::Cqueue() {
	arr = new int[10];
	capacity = 10;
	front = 4, rear = 4;
}

Cqueue::~Cqueue() {
	delete[] arr;
}

void Cqueue::enqueue(int item) {
	rear = (rear + 1) % capacity;
	if (isFull()) cqueueFull();
	arr[rear] = item;
}

int Cqueue::dequeue() {
	if (isEmpty()) {
		cout << "cqueue가 비어있습니다.\n";
		return -1;
	}
	front = (front + 1) % capacity;
	return arr[front];
}

bool Cqueue::isEmpty() {
	return front == rear;
}

bool Cqueue::isFull() {
	return front == rear;
}

void Cqueue::cqueueFull() {
	int* newArr = new int[capacity * 2];

	int start = (front + 1) % capacity;
	if (start < 2) {
		myCopy(arr + start, arr + start + capacity - 1, newArr);
	}
	else {
		myCopy(arr + start, arr + capacity, newArr);
		myCopy(arr, arr + rear + 1, newArr + capacity - start);
	}
	front = 2 * capacity - 1;
	rear = capacity - 1;
	capacity *= 2;

	delete[] arr;
	arr = newArr;
	cout << "queue의 사이즈를 늘렸습니다.\n";
}

void Cqueue::myCopy(int* a, int* b, int* c) {
	int i = 0;
	while (true) {
		if ((a + i) >= b) break;
		c[i] = a[i];
		i++;
	}
}

void Cqueue::printCqueue() {
	cout << "\nindex : item\n";
	if (!isEmpty()) {
		int i = getFront();
		do {
			i = (i + 1) % getCapacity();
			cout << i << " : " << getArr()[i] << endl;
			if (i == getRear()) break;
		} while (i != getFront());
	}
}


int main() {
	cout << "4.1. 스택\n";
	Stack stk;

	for (int i = 0; i < SIZE; i++) {
		stk.push(i);
		stk.printStack();
	}
	cout << "\n*******************************\n";

	for (int i = 0; i < SIZE; i++) {
		stk.pop();
		stk.printStack();
	}
	cout << "\n*******************************\n";


	cout << "\n4.2. 큐\n";
	Queue qu;

	for (int i = 0; i < SIZE; i++) {
		qu.enqueue(i);
		qu.printQueue();
	}
	cout << "\n*******************************\n";

	for (int i = 0; i < SIZE; i++) {
		qu.dequeue();
		qu.printQueue();
	}
	cout << "\n*******************************\n";

	printf("\n4.3. 원형큐\n");
	Cqueue cqu;

	for (int i = 0; i < SIZE; i++) {
		cqu.enqueue(i);
		cqu.printCqueue();
	}
	cout << "\n*******************************\n";

	for (int i = 0; i < SIZE; i++) {
		cqu.dequeue();
		cqu.printCqueue();
	}
	cout << "\n*******************************\n";

	return 0;
}
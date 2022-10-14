#include <iostream>
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
	int* newArr = new int[capacity*2];
	copy(arr, arr + capacity, newArr);
	delete[] arr;
	capacity *= 2;
	arr = newArr;
	newArr = NULL;
	cout << "stack의 사이즈를 늘렸습니다.\n";
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

int main() {
	cout << "4.1. 스택\n";
	int op, item;
	Stack stk;

	while (1) {
		cout << "\n스택 - 1.push 2.pop : ";
		cin >> op;
		if (op == -1) break;
		switch (op) {
		case 1:
			cout << "push item : ";
			cin >> item;
			stk.push(item);
			break;
		case 2:
			item = stk.pop();
			if (item != -1) cout << "pop item : " << item << endl;
			break;
		default:
			cout << "잘못된 입력\n";
		}
		cout << "index : item\n";
		if (!stk.isEmpty()) {
			for (int i = 0; i <= stk.getTop(); i++)
				cout << i << " : " << stk.getArr()[i] << endl;
		}
	}


	cout << "\n4.2. 큐\n";
	Queue qu;
	while (1) {
		cout << "\n큐 - 1.addQ 2.deleteQ : ";
		cin >> op;
		if (op == -1) break;
		switch (op) {
		case 1:
			cout << "addQ item : ";
			cin >> item;
			qu.enqueue(item);
			break;
		case 2:
			item = qu.dequeue();
			if (item != -1) cout << "deleteQ item : " << item << "\n";
			break;
		default:
			cout << "잘못된 입력\n";
		}
		cout << "index : item\n";
		if (!qu.isEmpty()) {
			for (int i = qu.getFront() + 1; i <= qu.getRear(); i++) cout << i << " : " << qu.getArr()[i] << endl;
		}
	}


	printf("\n4.3. 원형큐\n");
	Cqueue cqu;
	while (1) {
		cout << "\n원형큐 - 1.addCQ 2.deleteCQ : ";
		cin >> op;
		if (op == -1) break;
		switch (op) {
		case 1:
			cout << "addCQ item : ";
			cin >> item;
			cqu.enqueue(item);
			break;
		case 2:
			item = cqu.dequeue();
			if (item != -1) cout << "deleteCQ item : " << item << "\n";
			break;
		default:
			cout << "잘못된 입력\n";
			continue;
		}
		if (!cqu.isEmpty()) {
			cout << "index : item\n";
			int i = cqu.getFront();
			do {
				i = (i + 1) % cqu.getCapacity();
				cout << i << " : " << cqu.getArr()[i] << endl;
				if (i == cqu.getRear()) break;
			} while (i != cqu.getFront());
		}
	}

	return 0;
}
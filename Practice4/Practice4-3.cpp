#include <iostream>
#include <string>
using namespace std;

template <typename T1>
class Stack {
	T1* arr;
	int top;
	int capacity;
public:
	Stack();
	~Stack();

	T1* getArr() { return arr; }
	int getTop() { return top; }
	int getCapacity() { return capacity; }

	void push(T1);
	T1 pop();

	bool isEmpty();
	bool isFull();
	void stackFull();
	void printStack();
};

template <typename T1>
Stack<T1>::Stack() {
	arr = new T1[10];
	capacity = 10;
	top = -1;
}

template <typename T1>
Stack<T1>::~Stack() {
	delete[] arr;
}

template <typename T1>
void Stack<T1>::push(T1 item) {
	if (isFull()) stackFull();
	arr[++top] = item;
}

template <typename T1>
T1 Stack<T1>::pop() {
	if (isEmpty()) {
		cout << "Stack이 비어있습니다.\n";
		return -1;
	}
	return arr[top--];
}

template <typename T1>
bool Stack<T1>::isEmpty() {
	return top == -1;
}

template <typename T1>
bool Stack<T1>::isFull() {
	return top == capacity - 1;
}

template <typename T1>
void Stack<T1>::stackFull() {
	T1* newArr = new T1[capacity * 2];
	copy(arr, arr + capacity, newArr);
	delete[] arr;
	capacity *= 2;
	arr = newArr;
	newArr = NULL;
	cout << "stack의 사이즈를 늘렸습니다.\n";
}

template <typename T1>
void Stack<T1>::printStack() {
	cout << "\nindex : item\n";
	if (!isEmpty()) {
		for (int i = 0; i <= getTop(); i++)
			cout << i << " : " << getArr()[i] << endl;
	}
}

template <typename T2>
class Queue {
	T2* arr;
	int front;
	int rear;
	int capacity;
public:
	Queue();
	~Queue();

	T2* getArr() { return arr; }
	int getFront() { return front; }
	int getRear() { return rear; }
	int getCapacity() { return capacity; }

	void enqueue(T2);
	T2 dequeue();

	bool isEmpty();
	bool isFull();
	void queueFull();
	void printQueue();
};

template <typename T2>
Queue<T2>::Queue() {
	arr = new T2[10];
	capacity = 10;
	front = -1, rear = -1;
}

template <typename T2>
Queue<T2>::~Queue() {
	delete[] arr;
}

template <typename T2>
void Queue<T2>::enqueue(T2 item) {
	if (isFull()) queueFull();
	arr[++rear] = item;
}

template <typename T2>
T2 Queue<T2>::dequeue() {
	if (isEmpty()) {
		cout << "queue이 비어있습니다.\n";
		return -1;
	}
	return arr[++front];
}

template <typename T2>
bool Queue<T2>::isEmpty() {
	return front == rear;
}

template <typename T2>
bool Queue<T2>::isFull() {
	return rear == capacity - 1;
}

template <typename T2>
void Queue<T2>::queueFull() {
	T2* newArr = new T2[capacity * 2];
	copy(arr, arr + capacity, newArr);
	delete[] arr;
	capacity *= 2;
	arr = newArr;
	newArr = NULL;
	cout << "queue의 사이즈를 늘렸습니다.\n";
}

template <typename T2>
void Queue<T2>::printQueue() {
	cout << "\nindex : item\n";
	if (!isEmpty()) {
		for (int i = getFront() + 1; i <= getRear(); i++)
			cout << i << " : " << getArr()[i] << endl;
	}
}

template <typename T3>
class Cqueue {
	T3* arr;
	int front;
	int rear;
	int capacity;
public:
	Cqueue();
	~Cqueue();

	T3* getArr() { return arr; }
	int getFront() { return front; }
	int getRear() { return rear; }
	int getCapacity() { return capacity; }

	void enqueue(T3);
	T3 dequeue();

	bool isEmpty();
	bool isFull();
	void cqueueFull();
	void myCopy(T3*, T3*, T3*);
	void printCqueue();
};

template <typename T3>
Cqueue<T3>::Cqueue() {
	arr = new T3[10];
	capacity = 10;
	front = 4, rear = 4;
}

template <typename T3>
Cqueue<T3>::~Cqueue() {
	delete[] arr;
}

template <typename T3>
void Cqueue<T3>::enqueue(T3 item) {
	rear = (rear + 1) % capacity;
	if (isFull()) cqueueFull();
	arr[rear] = item;
}

template <typename T3>
T3 Cqueue<T3>::dequeue() {
	if (isEmpty()) {
		cout << "cqueue가 비어있습니다.\n";
		return -1;
	}
	front = (front + 1) % capacity;
	return arr[front];
}

template <typename T3>
bool Cqueue<T3>::isEmpty() {
	return front == rear;
}

template <typename T3>
bool Cqueue<T3>::isFull() {
	return front == rear;
}

template <typename T3>
void Cqueue<T3>::cqueueFull() {
	T3* newArr = new T3[capacity * 2];

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

template <typename T3>
void Cqueue<T3>::myCopy(T3* a, T3* b, T3* c) {
	int i = 0;
	while (true) {
		if ((a + i) >= b) break;
		c[i] = a[i];
		i++;
	}
}

template <typename T3>
void Cqueue<T3>::printCqueue() {
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
	int op;
	char item;
	Stack<char> stk;

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
	Queue<char> qu;
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
	Cqueue<char> cqu;
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
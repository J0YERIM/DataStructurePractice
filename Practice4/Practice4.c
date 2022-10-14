#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// stack 관련 변수
int* stack;
int max_stack_size = 10;
int top = -1;

// stack 관련 함수
int isFull(); // stack이 가득 찼을 경우 1 리턴, 아닐 경우 0 리턴
int isEmpty(); // stack이 비었을 경우 1 리턴, 아닐 경우 0 리턴
void stackFull(); // stack 사이즈 늘려주는 함수
void push(int); // push 함수
int pop(); // pop 함수

// queue 관련 변수
int* queue;
int max_queue_size = 10;
int front = -1, rear = -1;

// queue 관련 함수
int isFull_q();
int isEmpty_q();
void queueFull();
void add_q(int);
int delete_q();

// circular queue 관련 변수
int* cqueue;
int max_cqueue_size = 10;
int front_cq = 4, rear_cq = 4;

// circular queue 관련 함수
int isFull_cq();
int isEmpty_cq();
void cqueueFull();
void add_cq(int);
int delete_cq();
void copy(int*, int*, int*);

int main() {
	printf("4.1. 스택\n");
	int op, item;
	stack = (int*)malloc(max_stack_size * sizeof(int));
	while (1) {
		printf("\n스택 - 1.push 2.pop : ");
		scanf("%d", &op);
		if (op == -1) break;
		switch (op) {
		case 1:
			printf("push item : ");
			scanf("%d", &item);
			push(item);
			break;
		case 2:
			item = pop();
			if (item != -1) printf("pop item : %d\n", item);
			break;
		default:
			printf("잘못된 입력\n");
		}
		printf("top : %d\n", top);
		if (!isEmpty()) {
			printf("index : item\n");
			for (int i = 0; i <= top; i++) printf("%d : %d\n", i, stack[i]);
		}
	}
	free(stack);


	printf("\n4.2. 큐\n");
	queue = (int*)malloc(max_queue_size * sizeof(int));
	while (1) {
		printf("\n큐 - 1.addQ 2.deleteQ : ");
		scanf("%d", &op);
		if (op == -1) break;
		switch (op) {
		case 1:
			printf("addQ item : ");
			scanf("%d", &item);
			add_q(item);
			break;
		case 2:
			item = delete_q();
			if (item != -1) printf("deleteQ item : %d\n", item);
			break;
		default:
			printf("잘못된 입력\n");
		}
		printf("\nfront : %d | rear : %d\n", front, rear);
		if (!isEmpty_q()) {
			printf("index : item\n");
			for (int i = front + 1; i <= rear; i++) printf("%d : %d\n", i, queue[i]);
		}
	}
	free(queue);


	printf("\n4.3. 원형큐\n");
	cqueue = (int*)malloc(max_cqueue_size * sizeof(int));
	while (1) {
		printf("\n원형큐 - 1.addCQ 2.deleteCQ : ");
		scanf("%d", &op);
		if (op == -1) break;
		switch (op) {
		case 1:
			printf("addCQ item : ");
			scanf("%d", &item);
			add_cq(item);
			break;
		case 2:
			item = delete_cq();
			if (item != -1) printf("deleteCQ item : %d\n", item);
			break;
		default:
			printf("잘못된 입력\n");
			continue;
		}
		printf("\nfront : %d | rear : %d\n", front_cq, rear_cq);
		if (!isEmpty_cq()) {
			printf("index : item\n");
			int i = front_cq;
			do {
				i = (i + 1) % max_cqueue_size;
				printf("%d : %d\n", i, cqueue[i]);
				if (i == rear_cq) break;
			} while (i != front_cq);
		}
	}
	free(cqueue);
}

int isFull() {
	if (top >= max_stack_size - 1) return 1;
	else return 0;
}

int isEmpty() {
	if (top < 0) return 1;
	else return 0;
}

void stackFull() {
	max_stack_size *= 2;
	stack = (int*)realloc(stack, max_stack_size * sizeof(int));
	printf("stack의 사이즈를 늘렸습니다.\n");
}

void push(int item) {
	if (isFull()) stackFull();
	stack[++top] = item;
}

int pop() {
	if (isEmpty()) {
		printf("stack이 비어있습니다.\n");
		return -1;
	}
	return stack[top--];
}

int isFull_q() {
	if (rear == max_queue_size - 1) return 1;
	else return 0;
}

int isEmpty_q() {
	if (front == rear) return 1;
	else return 0;
}

void queueFull() {
	max_queue_size *= 2;
	queue = (int*)realloc(queue, max_queue_size * sizeof(int));
	printf("queue의 사이즈를 늘렸습니다.\n");
}

void add_q(int item) {
	if (isFull_q()) queueFull();
	queue[++rear] = item;
}

int delete_q() {
	if (isEmpty_q()) {
		printf("queue가 비어있습니다.\n");
		return -1;
	}
	return queue[++front];
}

int isFull_cq() {
	if (front_cq == rear_cq) return 1;
	else return 0;
}

int isEmpty_cq() {
	if (front_cq == rear_cq) return 1;
	else return 0;
}

void cqueueFull() {
	int* newQueue = (int*)malloc(2 * max_cqueue_size * sizeof(int));

	int start = (front_cq + 1) % max_cqueue_size;
	if (start < 2) {
		copy(cqueue + start, cqueue + start + max_cqueue_size - 1, newQueue);
	}
	else {
		copy(cqueue + start, cqueue + max_cqueue_size, newQueue);
		copy(cqueue, cqueue + rear_cq + 1, newQueue + max_cqueue_size - start);
	}
	front_cq = 2 * max_cqueue_size - 1;
	rear_cq = max_cqueue_size - 1;
	max_cqueue_size *= 2;

	free(cqueue);
	cqueue = newQueue;
	printf("cqueue가 확장되었습니다.\n");
}

void add_cq(int item) {
	rear_cq = (rear_cq + 1) % max_cqueue_size;
	if (isFull_cq()) cqueueFull();
	cqueue[rear_cq] = item;
}

int delete_cq() {
	if (isEmpty_cq()) {
		printf("cqueue가 비어있습니다.\n");
		return -1;
	}
	front_cq = (front_cq + 1) % max_cqueue_size;
	return cqueue[front_cq];
}

void copy(int* a, int* b, int* c) {
	int i = 0;
	while (1) {
		if ((a + i) >= b) break;
		c[i] = a[i];
		i++;
	}
}
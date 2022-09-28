#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void swapChar(char*, char*); // char형 데이터를 swap해주는 함수
void swapInt(int*, int*); // int형 데이터를 swap해주는 함수
void permChar(char*, int, int); // char형 순열 함수
void permInt(int*, int, int); // int형 순열 함수

void main() {
	printf("2.1. 순열 알고리즘 호출\n");
	char A[][10] = { "GO", "BOY", "GIRL", "GIRLS" };
	for (int i = 0; i < 4; i++) {
		printf("제시 문자열 : %s\n", A[i]);
		permChar(A[i], 0, strlen(A[i]) - 1);
		printf("\n");
	}

	printf("\n2,2. 1부터 n사이의 숫자들을 이용한 순열\n");
	double duration;
	clock_t start;
	while (1) {
		int input;
		printf("입력 : ");
		scanf("%d", &input);
		if (input == -1) { // -1 입력 시 종료
			printf("종료\n");
			break;
		}
		else if (input > 32) { // 32 이상 수 입력 시 continue
			printf("입력 범위(1~32)를 벗어났습니다.\n");
			continue;
		}
		printf("순열 : \n");
		int* B = (int*)malloc(sizeof(int) * input); // 1~input까지 배열 생성
		for (int i = 0; i < input; i++) B[i] = i + 1; // 배열 값 초기화
		start = clock();
		permInt(B, 0, input - 1);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		free(B);
		printf("\n실행시간 : %lf\n", duration);
	}

	printf("\n2.3. 순열 원소 개수를 변화시키면서 실행 시간 관찰\n");
	double durationList[10];
	for (int i = 0; i < 10; i++) {
		int* C = (int*)malloc(sizeof(int) * (i + 1)); // 1~input까지 배열 생성
		for (int j = 0; j < i + 1; j++) C[j] = j + 1; // 배열 값 초기화
		start = clock();
		permInt(C, 0, i);
		durationList[i] = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		free(C);
		printf("\n");
	}
	printf("\t원소갯수\t실행시간\n");
	for (int i = 0; i < 10; i++) printf("\t%d\t%lf\n", i + 1, durationList[i]);
}

void permChar(char* list, int i, int n) {
	if (i == n) {
		for (int j = 0; j <= n; j++) printf("%c", list[j]); // 출력
		printf("\t");
	}
	else {
		for (int j = i; j <= n; j++) {
			swapChar(&list[i], &list[j]);
			permChar(list, i + 1, n);
			swapChar(&list[i], &list[j]);
		}
	}
}

void permInt(int* list, int i, int n) {
	if (i == n) {
		for (int j = 0; j <= n; j++) printf("%d", list[j]); // 출력
		printf("\t");
	}
	else {
		for (int j = i; j <= n; j++) {
			swapInt(&list[i], &list[j]);
			permInt(list, i + 1, n);
			swapInt(&list[i], &list[j]);
		}
	}
}

void swapChar(char* a, char* b) {
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void swapInt(int* a, int* b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
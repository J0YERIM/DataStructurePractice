#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX_SIZE 100000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void sort(int[], int); // 선택 정렬 함수
int is_sorted(int[], int); // 정렬 상태 확인 함수

void main(void) {
	int i;
	int A[MAX_SIZE];
	srand((unsigned)time(NULL)); // Initialize random number generator

	printf("1.1. 무작위 100,000개 정수 생성 및 정렬, 정렬 검사 수행\n");
	printf("1.1.1. 배열 A에 100,000개의 정수를 무작위로 생성하여 저장\n");
	for (i = 0; i < MAX_SIZE; i++) { // 배열 A에 100,000개의 정수를 무작위로 생성하여 저장
		A[i] = ((double)rand() / RAND_MAX) * (MAX_SIZE - 1) + 1; // RAND_MAX값보다 더 큰 범위인 1 ~ 100,000을 얻기 위함
		printf("%d	", A[i]);
	}
	printf("\n");

	printf("1.1.2. 배열 A에 무작위로 저장된 정수를 정렬\n");
	sort(A, MAX_SIZE); // 배열 A에 무작위로 저장된 정수를 정렬
	for (i = 0; i < MAX_SIZE; i++) // 정렬된 번호 출력
		printf("%d ", A[i]);
	printf("\n");

	printf("1.1.3. 배열 A에 정렬된 정수의 정렬 상태 확인\n");
	// 배열 A에 정렬된 정수의 정렬 상태 확인
	if (is_sorted(A, MAX_SIZE) == 1) printf("정렬 완료!!!\n");
	else printf("정렬 실패!!!\n");
}

void sort(int list[], int n) {
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[min])
				min = j;
		SWAP(list[i], list[min], temp); // 최솟값을 찾은 후 Swap
	}
}

int is_sorted(int list[], int n) {
	int i;
	for (i = 0; i < n - 1; i++) {
		if (list[i] > list[i + 1]) return 0;
	}
	return 1;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define compare(x,y) (((x)<(y))? -1 : ((x)==(y))? 0 : 1)
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define MAX_SIZE 100000

int binsearch(int[], int, int, int); // 이진 검색 함수
void sort(int [], int); // 선택 정렬 함수
int is_sorted(int[], int); // 정렬 상태 확인 함수

void main(void) {
	int i;
	int A[MAX_SIZE];
	char result[30] = "정렬 완료!!!";
	srand((unsigned)time(NULL)); // Initialize random number generator
	
	printf("1.3. 100,000개의 정수를 무작위로 생성하여 정렬 후 이진검색 수행\n");
	printf("1.3.1. 배열에 100,000개의 정수를 무작위로 생성하여 저장\n");
	for (i = 0; i < MAX_SIZE; i++) { // 배열에 100,000개의 정수를 무작위로 생성하여 저장
		A[i] = ((double)rand() / RAND_MAX) * (MAX_SIZE - 1) + 1; // RAND_MAX값보다 더 큰 범위인 1 ~ 100,000을 얻기 위함
	}
	printf("\t완료\n");

	printf("1.3.2. 배열에 무작위로 저장된 정수 정렬\n");
	sort(A, MAX_SIZE); // 선택 정렬
	printf("\t완료\n");

	printf("1.3.3. 배열에 정렬된 정수의 정렬 상태 확인\n");
	if (is_sorted(A, MAX_SIZE) == 0) strcpy_s(result, 30, "정렬안됨");
	printf("\t%s\n", result);

	while (1) {
		int searchNum;
		printf("검색 데이터( 1 ~ 100000) : ");
		scanf_s("%d", &searchNum);
		if (searchNum == -1) {
			printf("검색완료\n");
			break;
		}
		printf("검색 데이터:\t%d,\tCounter: %d\n", searchNum, binsearch(A, searchNum, 0, MAX_SIZE - 1));
	}
}

int binsearch(int list[], int searchnum, int left, int right) {
	int middle, cnt = 0;
	while (left <= right) {
		middle = (left + right) / 2;
		switch (compare(list[middle], searchnum)) {
		case -1:
			left = middle + 1;
			break;
		case 0:
			return cnt;
		case 1:
			right = middle - 1;
		}
		cnt++;
	}
	return -1;
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define MAX_SIZE 1000000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void sort(int[], int); // 선택 정렬 함수
int is_sorted(int[], int); // 정렬 상태 확인 함수

void main(void) {
	int size[] = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000 };
	int i, index = 0;
	int A[MAX_SIZE];
	double duration;
	char result[10] = "정렬됨";
	clock_t start;

	printf("1.2 배열의 크기를 100부터 1,000,000까지 바꾸면서 sort 함수의 실행 시간 측정\n");
	printf("    n    시간    정렬상태\n");
	while (1) {
		int n = size[index];
		for (i = 0; i < n; i++) A[i] = n - i; // 역순 정렬된 배열 생성
		start = clock();
		sort(A, n); // 정렬
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		if (is_sorted(A, n) == 0) strcpy_s(result, 10, "정렬안됨");
		printf("%4d    %f    %s\n", n, duration, result);

		if (n == 1000000) return;
		index++;
	}
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
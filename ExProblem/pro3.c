#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SIZE 2

/*
1.3절 연습문제 3번(p.18)
n개의 Boolean 변수 x1, ..., xn이 주어졌을 때,
이 변수들이 가질 수 있는 가능한 모든 진리 값의 조합을 구하고자 한다.
예를 들어 n = 2이면 <true, true>, <true, fasle>, <false, true>, <false, false>와 같은 네 가지 경우가 존재한다.
이를 구하는 C 프로그램을 작성하라
*/

int truth[] = { 0,1 };
int* result;

void perm(int cnt, int r);

int main() {
	int n;
	printf("n을 입력하세요 >> ");
	scanf("%d", &n);
	result = (int*)malloc(sizeof(int) * n);
	perm(0, n);
	free(result);
}

void perm(int cnt, int r) {
	if (cnt == r) {
		printf("<");
		for (int i = 0; i < r; i++) {
			if (result[i]) printf("True");
			else printf("False");

			if (i != r - 1) printf(", ");
		}
		printf(">\n");
		return;
	}

	for (int i = 0; i < SIZE; i++) {
		result[cnt] = truth[i];
		perm(cnt + 1, r);
	}
}
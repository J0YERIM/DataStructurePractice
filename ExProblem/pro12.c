#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 4
/*
1.3절 연습문제 12번(p.18)
S가 n개의 원소로 된 집합일 때 S의 멱집합(powerset)은 모든 가능한 S의 부분 집합이다.
poserset(S)를 계산하는 순환 함수를 작성하라.
*/

char data[] = { 'a', 'b', 'c', 'd' };
int include[SIZE];

void powerset(int S) {
	if (S == SIZE) {
		for (int i = 0; i < SIZE; i++) {
			if (include[i]) 
				printf("%c ", data[i]);
		}
		printf("\n");
		return;
	}

	include[S] = 0;
	powerset(S + 1);
	include[S] = 1;
	powerset(S + 1);
}

int main() {
	powerset(0);

	return 0;
}
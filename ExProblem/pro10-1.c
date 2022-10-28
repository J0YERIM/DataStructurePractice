#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100000

/*
1.3절 연습문제 10번(p.18)
Ackermann 함수는 다음과 같이 정의된다.
이 함수는 m, n의 값이 아주 작은 값에서도 급속히 증가하는 성질이 있다. 
이 함수를 계산하는 순환 함수나 반복 함수를 작성하라.
*/

int Ackermann(int m, int n);

int main() {
	int m, n;
	printf("m, n 입력 >> ");
	scanf("%d %d", &m, &n);
	printf("Ackermann(%d,%d) = %d", m, n, Ackermann(m, n));

	return 0;
}

int Ackermann(int m, int n) {
	int list[MAX_SIZE]; // 스택
	int esp = 0; // 스택의 마지막 원소를 가리키고 있음

	list[esp++] = m; // list[0] = m
	list[esp] = n; // list[1] = n

	// 결국엔 마지막에 A(0, k) 꼴이 나옴
	while (1) {
		if (esp == 0) return list[esp]; // 종료
		else if (list[esp - 1] == 0) {
			list[esp - 1] = list[esp] + 1;
			esp--;
		}
		else if (list[esp] == 0) { // n = 0일 경우
			list[esp - 1] = list[esp - 1] - 1;
			list[esp] = 1;
		}
		else { // 그 외 경우
			list[esp + 1] = list[esp] - 1;
			list[esp] = list[esp - 1];
			list[esp - 1] = list[esp - 1] - 1;
			esp++;
		}
	}
}
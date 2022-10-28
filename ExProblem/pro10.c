#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

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
}

int Ackermann(int m, int n) {
	if (m == 0)
		return (n + 1);
	else if (n == 0)
		return Ackermann(m - 1, 1);
	else
		return Ackermann(m - 1, Ackermann(m, n - 1));
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define COMPARE(x,y) (((x)<(y))? -1 : ((x)==(y))? 0 : 1)
#define SIZE 10

typedef struct {
	float coef; // 계수
	int expon; // 지수
	int size; // 배열 사이즈
} polynominal;

polynominal* padd(polynominal*, polynominal*); // 다항식 덧셈 함수
polynominal* psub(polynominal*, polynominal*); // 다항식 덧셈 함수
polynominal* pmul(polynominal*, polynominal*); // 다항식 곱셈 함수
polynominal* single_mul(polynominal, polynominal*); // 다항식-항 곱셈 함수 
double peval(polynominal* D, double b);
void printArray(polynominal*); // 배열 출력 함수
void sort(polynominal*); // 선택 정렬 함수
void swap(polynominal*, int, int); // swap 함수

int main() {
	printf("3.1. 다항식 생성\n");
	polynominal* A = (polynominal*)calloc(SIZE, sizeof(polynominal));
	polynominal* B = (polynominal*)calloc(SIZE, sizeof(polynominal));

	float coef; // 계수
	int expon; // 지수
	int i = 0;

	A->size = SIZE;
	B->size = SIZE;

	while (1) { // A 입력 받기
		printf("A(x)의 항을 입력하세요. (coef expon) : ");
		scanf("%f %d", &coef, &expon);
		if (coef == -1 && expon == -1) { // -1 입력 시 종료
			A[i].coef = -1;
			A[i].expon = -1;
			break;
		}
		A[i].coef = coef;
		A[i].expon = expon;
		i++;
		if (i == A->size) { // 배열이 꽉 차면 사이즈 +1
			A = (polynominal*)realloc(A, (++(A->size)) * sizeof(polynominal));
		}
	}
	sort(A); // 정렬
	i = 0; // 다시 0으로 초기화
	printf("다항식 A(x)\n"); // 배열 A 출력
	printf("\tcoef\texpon\n");
	printArray(A);

	while (1) { // B 입력 받기
		printf("B(x)의 항을 입력하세요. (coef expon) : ");
		scanf("%f %d", &coef, &expon);
		if (coef == -1 && expon == -1) { // -1 입력 시 종료
			B[i].coef = -1;
			B[i].expon = -1;
			break;
		}
		B[i].coef = coef;
		B[i].expon = expon;
		i++;
		if (i == B->size) { // 배열이 꽉 차면 사이즈 +1
			B = (polynominal*)realloc(B, (++(B->size)) * sizeof(polynominal));
		}
	}
	sort(B); // 정렬
	i = 0; // 다시 0으로 초기화
	printf("다항식 B(x)\n"); // 배열 B 출력
	printf("\tcoef\texpon\n");
	printArray(B);


	//printf("\n3.2. 다항식 덧셈\n");
	//polynominal* D = padd(A, B);
	//printf("다항식 덧셈 결과 : D(x)\n");
	//printf("\tcoef\texpon\n");
	//printArray(D);

	printf("\n3.2. 다항식 뺄셈\n");
	polynominal* D = psub(A, B);
	printf("다항식 뺄셈 결과 : D(x)\n");
	printf("\tcoef\texpon\n");
	printArray(D);

	printf("eval\n");
	double b;
	scanf("%lf", &b);
	double result = peval(D, b);
	printf("%lf", result);


	/*printf("\n3.3. 다항식 곱셉\n");
	D = pmul(A, B);
	printf("다항식 곱셈 결과 : D(x)\n");
	printf("\tcoef\texpon\n");
	printArray(D);

	free(A);
	free(B);
	free(D);*/
}

polynominal* padd(polynominal* A, polynominal* B) { // 다항식 덧셈 함수
	polynominal* result = (polynominal*)calloc(SIZE, sizeof(polynominal));
	result->size = SIZE;
	int aIndex = 0;
	int bIndex = 0;
	int resultIndex = 0;

	while (1) {
		if ((A[aIndex].coef == -1 && A[aIndex].expon == -1) || (B[bIndex].coef == -1 && B[bIndex].expon == -1)) break; // A, B 둘 중에 하나라도 배열이 끝나면 break
		switch (COMPARE(A[aIndex].expon, B[bIndex].expon)) {
		case -1: // a.expon < b.expon
			result[resultIndex].coef = B[bIndex].coef;
			result[resultIndex++].expon = B[bIndex++].expon;
			break;
		case 0: // a.expon == b.expon
			result[resultIndex].coef = A[aIndex].coef + B[bIndex].coef;
			result[resultIndex++].expon = A[aIndex].expon;
			aIndex++; bIndex++;
			break;
		case 1: // a.expon > b.expon
			result[resultIndex].coef = A[aIndex].coef;
			result[resultIndex++].expon = A[aIndex++].expon;
			break;
		}
		if (resultIndex == result->size) { // 배열이 꽉 차면 사이즈 +1 
			result = (polynominal*)realloc(result, (++(result->size)) * sizeof(polynominal));
		}
	}
	while (1) { // A가 끝나지 않을 경우
		if (A[aIndex].coef == -1 && A[aIndex].expon == -1) break;
		result[resultIndex].coef = A[aIndex].coef;
		result[resultIndex++].expon = A[aIndex++].expon;
		if (resultIndex == result->size) {
			result = (polynominal*)realloc(result, (++(result->size)) * sizeof(polynominal));
		}
	}

	while (1) { // B가 끝나지 않을 경우
		if (B[bIndex].coef == -1 && B[bIndex].expon == -1) break;
		result[resultIndex].coef = B[bIndex].coef;
		result[resultIndex++].expon = B[bIndex++].expon;
		if (resultIndex == result->size) {
			result = (polynominal*)realloc(result, (++(result->size)) * sizeof(polynominal));
		}
	}

	result[resultIndex].coef = -1;
	result[resultIndex].expon = -1;

	return result;
}

polynominal* psub(polynominal* A, polynominal* B) { // 다항식 덧셈 함수
	polynominal* result = (polynominal*)calloc(SIZE, sizeof(polynominal));
	result->size = SIZE;
	int aIndex = 0;
	int bIndex = 0;
	int resultIndex = 0;

	while (1) {
		if ((A[aIndex].coef == -1 && A[aIndex].expon == -1) || (B[bIndex].coef == -1 && B[bIndex].expon == -1)) break; // A, B 둘 중에 하나라도 배열이 끝나면 break
		switch (COMPARE(A[aIndex].expon, B[bIndex].expon)) {
		case -1: // a.expon < b.expon
			result[resultIndex].coef = -B[bIndex].coef;
			result[resultIndex++].expon = B[bIndex++].expon;
			break;
		case 0: // a.expon == b.expon
			result[resultIndex].coef = A[aIndex].coef - B[bIndex].coef;
			result[resultIndex++].expon = A[aIndex].expon;
			aIndex++; bIndex++;
			break;
		case 1: // a.expon > b.expon
			result[resultIndex].coef = A[aIndex].coef;
			result[resultIndex++].expon = A[aIndex++].expon;
			break;
		}
		if (resultIndex == result->size) { // 배열이 꽉 차면 사이즈 +1 
			result = (polynominal*)realloc(result, (++(result->size)) * sizeof(polynominal));
		}
	}
	while (1) { // A가 끝나지 않을 경우
		if (A[aIndex].coef == -1 && A[aIndex].expon == -1) break;
		result[resultIndex].coef = A[aIndex].coef;
		result[resultIndex++].expon = A[aIndex++].expon;
		if (resultIndex == result->size) {
			result = (polynominal*)realloc(result, (++(result->size)) * sizeof(polynominal));
		}
	}

	while (1) { // B가 끝나지 않을 경우
		if (B[bIndex].coef == -1 && B[bIndex].expon == -1) break;
		result[resultIndex].coef = B[bIndex].coef;
		result[resultIndex++].expon = B[bIndex++].expon;
		if (resultIndex == result->size) {
			result = (polynominal*)realloc(result, (++(result->size)) * sizeof(polynominal));
		}
	}

	result[resultIndex].coef = -1;
	result[resultIndex].expon = -1;

	return result;
}

double peval(polynominal* D, double b) {
	int i = 0;
	double result = 0;
	while (1) {
		if (D[i].coef == -1 && D[i].expon == -1) break;
		result += (D[i].coef)*(pow(b, D[i].expon));
		i++;
	}
	return result;
}

polynominal* pmul(polynominal* A, polynominal* B) { // 다항식 곱셈 함수
	polynominal* result = NULL;
	int aIndex = 0;
	int resultIndex = 0;
	int i = 1;

	while (1) {
		if (A[aIndex].coef == -1 && A[aIndex].expon == -1) break;
		polynominal* Ci = single_mul(A[aIndex++], B);
		sort(Ci);

		printf("singul_mul - C%d(x)\n", i);
		printf("\tcoef\texpon\n");
		printArray(Ci);

		if (i == 1) {
			result = Ci;
		}
		else {
			result = padd(result, Ci);
		}

		sort(result);
		i++;
	}

	return result;
}

polynominal* single_mul(polynominal A, polynominal* B) {
	polynominal* result = (polynominal*)calloc(SIZE, sizeof(polynominal));
	int bIndex = 0;
	int resultIndex = 0;
	result->size = SIZE;

	while (1) {
		if (B[bIndex].coef == -1 && B[bIndex].expon == -1) break;

		result[resultIndex].expon = B[bIndex].expon + A.expon;
		result[resultIndex++].coef = B[bIndex++].coef * A.coef;

		if (resultIndex == result->size) {
			result = (polynominal*)realloc(result, (++(result->size)) * sizeof(polynominal));
		}
	}

	result[resultIndex].coef = -1;
	result[resultIndex].expon = -1;

	return result;
}

void printArray(polynominal* arr) { // 배열 출력 함수
	int i = 0;
	while (1) {
		if (arr[i].coef == -1 && arr[i].expon == -1) break;
		printf("\t%.2f\t%d\n", arr[i].coef, arr[i].expon);
		i++;
	}
}

void sort(polynominal* arr) { // 선택 정렬 함수
	int i, j, max;
	for (i = 0; !(arr[i].coef == -1 && arr[i].expon == -1); i++) {
		max = i;
		for (j = i + 1; !(arr[j].coef == -1 && arr[j].expon == -1); j++)
			if (arr[j].expon > arr[max].expon)
				max = j;
		swap(arr, i, max);
	}
}

void swap(polynominal* arr, int a, int b) { // swap 함수
	float coefTemp;
	int exponTemp;

	coefTemp = arr[a].coef;
	exponTemp = arr[a].expon;

	arr[a].coef = arr[b].coef;
	arr[a].expon = arr[b].expon;

	arr[b].coef = coefTemp;
	arr[b].expon = exponTemp;
}
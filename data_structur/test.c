#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101
typedef struct {
	float coef;
	int expon;
} polynomial;
polynomial terms[MAX_TERMS] = { { 8, 3 }, { 7, 1 }, { 1, 0 }, { 10, 3 }, { 3, 2 }, { 1, 0 } };
int avail = 6;

//두개의 정수를 비교
char compare(int a, int b)
{
	if (a > b) return '>';
	else if (a == b) return '=';
	else return '<';
}

//새로운 항을 다항식에 추가한다.
void attach(float coefficient, int exponent)
{
	if (avail >= MAX_TERMS) { // 배열 경계 검사 수정
		fprintf(stderr, "항의 개수가 너무 많음\n");
		exit(1);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}

//C = A + B
void poly_add(int As, int Ae, int Bs, int Be, int* Cs, int* Ce)
{
	float tempcoef;
	*Cs = avail;
	while (As <= Ae && Bs <= Be)
		switch (compare(terms[As].expon, terms[Bs].expon))
		{
		case '>': //A차수 > B차수
			attach(terms[As].coef, terms[As].expon);
			As++;
			break;
		case '=':	//A차수 == B차수
			tempcoef = terms[As].coef + terms[Bs].coef;
			if (tempcoef)
				attach(tempcoef, terms[As].expon);
			As++; Bs++;
			break;
		case '<':	//A차수 < B차수
			attach(terms[Bs].coef, terms[Bs].expon);
			Bs++;
			break;
		}
	// A의 나머지 항들을 이동함
	for (; As <= Ae; As++)
		attach(terms[As].coef, terms[As].expon);
	//B의 나머지 항들을 이동함
	for (; Bs <= Be; Bs++)
		attach(terms[Bs].coef, terms[Bs].expon);
	*Ce = avail - 1;
}

int main() {
	int As = 0, Ae = 2; // 다항식 A의 시작과 끝 인덱스
	int Bs = 3, Be = 5; // 다항식 B의 시작과 끝 인덱스
	int Cs, Ce;         // 다항식 C의 시작과 끝 인덱스

	poly_add(As, Ae, Bs, Be, &Cs, &Ce);

	printf("다항식 A: ");
	for (int i = As; i <= Ae; i++) {
		printf("%.1fx^%d ", terms[i].coef, terms[i].expon);
		if (i < Ae) printf("+ ");
	}
	printf("\n");

	printf("다항식 B: ");
	for (int i = Bs; i <= Be; i++) {
		printf("%.1fx^%d ", terms[i].coef, terms[i].expon);
		if (i < Be) printf("+ ");
	}
	printf("\n");

	printf("다항식 C = A + B: ");
	for (int i = Cs; i <= Ce; i++) {
		printf("%.1fx^%d ", terms[i].coef, terms[i].expon);
		if (i < Ce) printf("+ ");
	}
	printf("\n");

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS	//scanf 오류 방지
#include <stdio.h>	//입출력 값을 쓰기위한 헤더파일
#include <stdlib.h> //exit()함수 사용을 위한 헤더파일
#define MAX_TERMS 101	// 다항식 최대 항 개수정의
typedef struct {	//구조체 생성
	float coef;		//계수
	int expon;		//지수
}polynomial;		//구조체 이름

//다항식의 항들의 저장하는 배열 선언,최대 MAX_TERMS가능
polynomial terms[MAX_TERMS] = { { 8, 3 }, { 7, 1 }, { 1, 0 }, { 10, 3 }, { 3, 2 }, { 1, 0 } };//
int avail = 6;//6개 항목

//두개의 정수를 비교하여 결과를 반환하는 함수
char compare(int a, int b)
{
	if (a > b) return '>';	//a > b이면 > 반환
	else if (a == b) return '=';	//a = b이면 = 반환
	else return '<';	//a < b이면 < 반환
}

//새로운 항을 다항식에 추가한다.
void attach(float coefficient, int exponent)
{
	if (avail >= MAX_TERMS) {	//항의 계수가 초과하면 실행 안 함
		fprintf(stderr, "항의 개수가 너무 많음\n");//오류메시지 출력
		exit(1);	//프로그램 종료
	}
	terms[avail].coef = coefficient;	//새로운 항에 계수 저장
	terms[avail++].expon = exponent;	//새로운 항의 지수 저장 후 avil+1
}

//C = A + B
void poly_add(int As, int Ae, int Bs, int Be, int* Cs, int* Ce)
{
	float tempcoef;	//임시로 계수를 저장할 변수
	*Cs = avail;	//
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
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

//�ΰ��� ������ ��
char compare(int a, int b)
{
	if (a > b) return '>';
	else if (a == b) return '=';
	else return '<';
}

//���ο� ���� ���׽Ŀ� �߰��Ѵ�.
void attach(float coefficient, int exponent)
{
	if (avail >= MAX_TERMS) { // �迭 ��� �˻� ����
		fprintf(stderr, "���� ������ �ʹ� ����\n");
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
		case '>': //A���� > B����
			attach(terms[As].coef, terms[As].expon);
			As++;
			break;
		case '=':	//A���� == B����
			tempcoef = terms[As].coef + terms[Bs].coef;
			if (tempcoef)
				attach(tempcoef, terms[As].expon);
			As++; Bs++;
			break;
		case '<':	//A���� < B����
			attach(terms[Bs].coef, terms[Bs].expon);
			Bs++;
			break;
		}
	// A�� ������ �׵��� �̵���
	for (; As <= Ae; As++)
		attach(terms[As].coef, terms[As].expon);
	//B�� ������ �׵��� �̵���
	for (; Bs <= Be; Bs++)
		attach(terms[Bs].coef, terms[Bs].expon);
	*Ce = avail - 1;
}

int main() {
	int As = 0, Ae = 2; // ���׽� A�� ���۰� �� �ε���
	int Bs = 3, Be = 5; // ���׽� B�� ���۰� �� �ε���
	int Cs, Ce;         // ���׽� C�� ���۰� �� �ε���

	poly_add(As, Ae, Bs, Be, &Cs, &Ce);

	printf("���׽� A: ");
	for (int i = As; i <= Ae; i++) {
		printf("%.1fx^%d ", terms[i].coef, terms[i].expon);
		if (i < Ae) printf("+ ");
	}
	printf("\n");

	printf("���׽� B: ");
	for (int i = Bs; i <= Be; i++) {
		printf("%.1fx^%d ", terms[i].coef, terms[i].expon);
		if (i < Be) printf("+ ");
	}
	printf("\n");

	printf("���׽� C = A + B: ");
	for (int i = Cs; i <= Ce; i++) {
		printf("%.1fx^%d ", terms[i].coef, terms[i].expon);
		if (i < Ce) printf("+ ");
	}
	printf("\n");

	return 0;
}
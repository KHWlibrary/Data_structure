#define _CRT_SECURE_NO_WARNINGS  // �� �� ���� �־�� ��
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return s->top == -1;
}

int is_full(StackType* s) {
	return s->top == MAX_STACK_SIZE - 1;
}

void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		exit(1);
	}
	s->data[++(s->top)] = item;
}

element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	return s->data[(s->top)--];
}

int main(void) {
	StackType s;
	init_stack(&s);

	int num;
	printf("������ �Է��Ͻÿ�: ");
	scanf("%d", &num);  // ?? scanf_s �� �����ϳ�, scanf�� �ᵵ ��� ���� ����˴ϴ�

	if (num == 0) {
		printf("������ ����: 0\n");
		return 0;
	}
	if (num < 0) {
		printf("������ ������� �ʽ��ϴ�.\n");
		return 0;
	}

	int original = num;

	while (num > 0) {
		push(&s, num % 10);  // �ڸ����� ���ÿ� ����
		num /= 10;
	}

	printf("�Է��� ����: %d\n", original);
	printf("������ ����: ");
	while (!is_empty(&s)) {
		printf("%d", pop(&s));  // ���ÿ��� ������ �Ųٷ� ���
	}
	printf("\n");

	return 0;
}

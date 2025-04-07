#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// ���� �ʱ�ȭ
void init_stack(StackType* s) {
	s->top = -1;
}

// ���� ����
int is_empty(StackType* s) {
	return (s->top == -1);
}

// ��ȭ ����
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

// ����
void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	s->data[++(s->top)] = item;
}

// ����
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	return s->data[(s->top)--];
}

// ��ũ
element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	return s->data[s->top];
}

// ����1: �ϴܺ��� ��ܱ��� ���
void print1(StackType* ps) {
	if (is_empty(ps)) return;
	for (int i = 0; i <= ps->top; i++)
		printf("%d ", ps->data[i]);
}

// ����2: ��ܺ��� �ϴܱ��� ���
void print2(StackType* ps) {
	if (is_empty(ps)) return;
	for (int i = ps->top; i >= 0; i--)
		printf("%d ", ps->data[i]);
}

int main() {
	StackType s1, s2;
	init_stack(&s1);
	init_stack(&s2);

	int select;
	element data;

	while (1) {
		printf("1.���� | 2.���� | 3.��� | 4.����: ");
		scanf("%d", &select);

		switch (select) {
		case 1:
			printf("������ �Է��ϼ���: ");
			scanf("%d", &data);
			push(&s1, data);
			break;
		case 2:
			if (is_empty(&s2)) {
				while (!is_empty(&s1)) {
					push(&s2, pop(&s1));
				}
			}
			if (!is_empty(&s2)) {
				printf("������ ��: %d\n", pop(&s2));
			}
			else {
				printf("ť�� ��� �ֽ��ϴ�.\n");
			}
			break;
		case 3:
			printf("ť ���� (front -> rear): ");
			print2(&s2);  // s2�� front ��
			print1(&s1);  // s1�� rear ��
			printf("\n");
			break;
		case 4:
			return 0;
		default:
			printf("�ùٸ� �޴��� �����ϼ���.\n");
		}
	}
}

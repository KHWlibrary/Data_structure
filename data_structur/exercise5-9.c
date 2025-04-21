// 2���� ������ ����Ͽ� ť�� �����غ���.
// �Է��� ������ ���� #1�� �ִ´�.
// ��� ��û�� ������ ���� #2���� ��Ҹ� ������.
// ���� #2�� ������� ���� ���� #1�� ��� ��Ҹ� ������ ���� #2�� �ִ´�.

#define _CRT_SECURE_NO_WARNINGS     // scanf ���� ��� ���ſ�
#include <stdio.h>                  // ǥ�� ����� �Լ�
#include <stdlib.h>                 // exit �Լ� �� ǥ�� ���̺귯��

#define MAX_STACK_SIZE 100          // ���� �ϳ��� �ִ� ũ�� ����

// ���ÿ� ����� ������ Ÿ�� ���� (������)
typedef int element;

// ���� ����ü ����
typedef struct {
	element data[MAX_STACK_SIZE];  // �����͸� ������ �迭
	int top;                       // top�� ���� ������ ����⸦ ����Ŵ
} StackType;

// ������ �ʱ�ȭ�ϴ� �Լ�
void init_stack(StackType* s) {
	s->top = -1;                   // �ʱ⿡�� �ƹ��͵� �����Ƿ� -1�� ����
}

// ������ ����ִ��� Ȯ���ϴ� �Լ�
int is_empty(StackType* s) {
	return (s->top == -1);        // top�� -1�̸� �������
}

// ������ ���� á���� Ȯ���ϴ� �Լ�
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));  // top�� �ִ� �ε����� �����ߴ��� Ȯ��
}

// ���ÿ� �����͸� �����ϴ� �Լ� (push)
void push(StackType* s, element item) {
	if (is_full(s)) {             // ���� �� ��� ���� ���
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	s->data[++(s->top)] = item;  // top�� 1 ������Ű�� �ش� ��ġ�� �� ����
}

// ���ÿ��� �����͸� �����ϴ� �Լ� (pop)
element pop(StackType* s) {
	if (is_empty(s)) {           // ����ִ� ��� ���� ��� �� ����
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	return s->data[(s->top)--];  // ���� top�� ���� ��ȯ�ϰ� top�� ����
}

// ������ �ֻ�� ���� Ȯ���ϴ� �Լ� (peek)
element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	return s->data[s->top];      // top ��ġ�� ���� ��ȯ (�������� ����)
}

// ���� 1�� ������ ����ϴ� �Լ� (bottom �� top)
void print1(StackType* ps) {
	if (is_empty(ps)) return;    // ��������� �ƹ��͵� ������� ����
	for (int i = 0; i <= ps->top; i++)  // �Ʒ����� ������ ���� ���
		printf("%d ", ps->data[i]);
}

// ���� 2�� ������ ����ϴ� �Լ� (top �� bottom)
void print2(StackType* ps) {
	if (is_empty(ps)) return;    // ��������� �ƹ��͵� ������� ����
	for (int i = ps->top; i >= 0; i--)  // ������ �Ʒ��� ���
		printf("%d ", ps->data[i]);
}

// ���� �Լ� - ť�� ���� 2���� ������ �������̽�
int main() {
	StackType s1, s2;            // ���� 2�� ����
	init_stack(&s1);             // s1 �ʱ�ȭ
	init_stack(&s2);             // s2 �ʱ�ȭ

	int select;                  // ����� �޴� ���ÿ� ����
	element data;                // ������ ������

	while (1) {                  // ���� ���� - ���� ���ǿ��� ��������
		printf("1.���� | 2.���� | 3.��� | 4.����: ");
		scanf("%d", &select);   // ����ڷκ��� ���� �Է�

		switch (select) {
		case 1:  // ���� ����
			printf("������ �Է��ϼ���: ");
			scanf("%d", &data); // ������ �Է�
			push(&s1, data);    // ���� 1�� push (enqueue ����)
			break;

		case 2:  // ���� ����
			if (is_empty(&s2)) {              // ���� 2�� ����ִٸ�
				while (!is_empty(&s1)) {      // ���� 1�� ������� ���� ����
					push(&s2, pop(&s1));      // ���� 1�� ��� �����͸� ���� 2�� �ű�
				}
			}
			if (!is_empty(&s2)) {             // ���� 2�� ������� �ʴٸ�
				printf("������ ��: %d\n", pop(&s2)); // s2���� ������ ������ (dequeue ����)
			}
			else {
				printf("ť�� ��� �ֽ��ϴ�.\n"); // �� �� ��������� ��� �Ұ�
			}
			break;

		case 3:  // ��� ���� (ť ���� ����)
			printf("ť ���� (front -> rear): ");
			print2(&s2); // ���� 2�� top�� front ����
			print1(&s1); // ���� 1�� bottom�� rear ����
			printf("\n");
			break;

		case 4:  // ����
			return 0;    // ���α׷� ���� ����

		default:
			printf("�ùٸ� �޴��� �����ϼ���.\n"); // �߸��� �Է� ó��
		}
	}
}

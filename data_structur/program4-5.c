#include<stdio.h>      // ǥ�� ����� �Լ� ����� ���� ��� ����
#include<stdlib.h>     // �޸� ���� �Ҵ� �� �Ϲ����� ��ƿ��Ƽ �Լ� ����� ���� ��� ����

#define MAX_STACK_SIZE 100   // (���� �ڵ忡�� ������ ������) ������ �ִ� ũ�⸦ �����ϴ� ��ũ��

typedef int element;         // element�� int�� �����Ͽ� �ڵ� ������ ���

// ���� ���� ������ ���� ����ü ����
typedef struct {
	element* data;      // ���� ��ҵ��� ������ ������ (���� �迭)
	int capacity;       // ������ ���� �뷮
	int top;            // ������ top �ε��� (���� �������� ���Ե� ����� ��ġ)
} StackType;

// ���� �ʱ�ȭ �Լ�: �ʱ� �뷮�� 1�� �����ϰ� �޸� �Ҵ�
void init_stack(StackType* s)
{
	s->top = -1;  // �ʱ⿡�� ������ ��� �����Ƿ� top�� -1�� ����
	s->capacity = 1;  // �ʱ� �뷮�� 1�� ����
	s->data = (element*)malloc(s->capacity * sizeof(element));  // ���� �޸� �Ҵ�
}

// ������ ��� �ִ��� Ȯ���ϴ� �Լ�
int is_empty(StackType* s)
{
	return(s->top == -1);  // top�� -1�̸� ��� �ִ� ����
}

// ������ ���� á���� Ȯ���ϴ� �Լ�
int is_full(StackType* s)
{
	return(s->top == (s->capacity - 1));  // top�� �뷮�� ������ ��ġ�� ������ ��ȭ ����
}

// ���ÿ� ��Ҹ� �߰��ϴ� �Լ� (�ʿ�� �뷮�� �� ��� �ø�)
void push(StackType* s, element item)
{
	if (is_full(s)) {  // ������ �� á�ٸ�
		s->capacity *= 2;  // �뷮�� �� ��� ����
		s->data = (element*)realloc(s->data, s->capacity * sizeof(element));  // ���Ҵ�
	}
	s->data[++(s->top)] = item;  // top�� ������Ű�� �ش� ��ġ�� item ����
}

// ���ÿ��� ��Ҹ� �����ϰ� ��ȯ�ϴ� �Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {  // ������ ��� ������
		fprintf(stderr, "���� ���� ����\n");  // ���� �޽��� ���
		exit(1);  // ������ ����
	}
	else return s->data[(s->top)--];  // top ��ġ�� ��Ҹ� ��ȯ�ϰ� top ����
}

// ���� �Լ�: ���� �׽�Ʈ
int main(void)
{
	StackType s;          // ���� ���� ����
	init_stack(&s);       // ���� �ʱ�ȭ

	push(&s, 1);          // ���ÿ� 1 �߰�
	push(&s, 2);          // ���ÿ� 2 �߰�
	push(&s, 3);          // ���ÿ� 3 �߰�

	printf("%d \n", pop(&s));  // 3 ��� (���� �������� �߰��� ��)
	printf("%d \n", pop(&s));  // 2 ���
	printf("%d \n", pop(&s));  // 1 ���

	free(s.data);         // ���� �Ҵ��� �޸� ����
	return 0;             // ���α׷� ����
}

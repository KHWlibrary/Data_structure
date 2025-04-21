#include<stdio.h>       // ǥ�� ����� �Լ� ����� ���� ���
#include<stdlib.h>      // ���� �޸�, exit �Լ� ���� ���� ���
#include<string.h>      // ���ڿ� ó�� �Լ� (strlen) ����� ���� ���

#define MAX_STACK_SIZE 100   // ���ÿ� ������ �� �ִ� �ִ� ��� ����

// ===== ���� �ڷᱸ�� ���� =====
typedef char element;   // ���ÿ� ������ ��Ҹ� ������(char)���� ����

// ����ü�� ���� ���� (���� ũ�� �迭 ���)
typedef struct {
	element data[MAX_STACK_SIZE];  // ���� ��ҵ��� ������ �迭
	int top;                       // ������ ���� ��(top) ����� �ε���
} StackType;

// ===== ���� ���� �Լ��� =====

// ������ �ʱ�ȭ�ϴ� �Լ� (ó���� top�� -1, �� ��� ����)
void init_stack(StackType* s)
{
	s->top = -1;
}

// ������ ��� �ִ��� Ȯ���ϴ� �Լ�
int is_empty(StackType* s)
{
	return(s->top == -1);  // top�� -1�̸� ���� ����
}

// ������ ���� á���� Ȯ���ϴ� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));  // top�� �迭 ���̸� ��ȭ ����
}

// ���ÿ� ��Ҹ� �߰��ϴ� �Լ� (���� - push ����)
void push(StackType* s, element item)
{
	if (is_full(s)) {  // ��ȭ �����̸� ���� �޽��� ���
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else {
		// top�� �ϳ� ������Ų �� �ش� ��ġ�� item ����
		s->data[++(s->top)] = item;
	}
}

// ���ÿ��� ��Ҹ� ������ �Լ� (���� - pop ����)
element pop(StackType* s)
{
	if (is_empty(s)) {  // ���� ���¸� ���� �� �����Ƿ� ���� ���
		fprintf(stderr, "���� ���� ����\n");
		exit(1);  // ���α׷� ���� ����
	}
	else {
		// top ��ġ�� ��Ҹ� ��ȯ�ϰ�, top�� ���ҽ�Ŵ
		return s->data[(s->top)--];
	}
}

// ������ top ��Ҹ� ������ �ʰ� ��ȯ (peek ����)
element peek(StackType* s)
{
	if (is_empty(s)) {  // ������ ��� ������ ���� ���
		fprintf(stderr, "���ð��鿡��\n");
		exit(1);
	}
	else {
		// ���� top ��ġ�� ��Ҹ� ��ȯ�� (������ ���� ����)
		return s->data[s->top];
	}
}

// ===== ��ȣ ¦ �˻� �Լ� =====

// ��ȣ�� �ùٸ��� ¦���������� Ȯ���ϴ� �Լ�
int check_matching(const char* in)
{
	StackType s;           // ���� ����
	char ch, open_ch;      // ���� ����, ���ÿ��� ���� ���� ��ȣ ���� ����
	int i, n = strlen(in); // ���ڿ� ���� ���
	init_stack(&s);        // ���� �ʱ�ȭ

	// ���ڿ��� �� ���ڵ��� �ϳ��� Ȯ��
	for (i = 0; i < n; i++) {
		ch = in[i];  // ���� ���� �ϳ��� ch�� ����

		// ���� ��ȣ�� ��� �� ���ÿ� push
		switch (ch) {
		case '(': case '[': case '{':
			push(&s, ch);  // ���ÿ� ����
			break;

			// �ݴ� ��ȣ�� ���
		case ')': case ']': case '}':
			if (is_empty(&s)) return 0;  // ������ ��������� ¦�� �� ����

			open_ch = pop(&s);  // ���� ��ȣ ������
			// ¦�� �´��� ��
			if ((open_ch == '(' && ch != ')') ||
				(open_ch == '[' && ch != ']') ||
				(open_ch == '{' && ch != '}')) {
				return 0;  // ¦�� �� ������ ����
			}
			break;
		}
	}

	// �ݺ��� ���� �Ŀ��� ���ÿ� �����ִٸ� ¦�� �� ���� ���� ��ȣ�� ����
	if (!is_empty(&s)) return 0;

	// ��� ��ȣ�� ���������� �������� ����
	return 1;
}

// ===== ���� �Լ� =====
int main(void)
{
	// ��ȣ ¦�� �´��� �˻��� ���ڿ�
	char* p = "{[(())]}";

	// �˻� ��� ���
	if (check_matching(p) == 1)
		printf("%s ��ȣ �˻� ����\n", p);
	else
		printf("%s ��ȣ �˻� ����\n", p);

	return 0;
}

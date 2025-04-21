#include<stdio.h>      // ǥ�� ����� �Լ� ���
#include<stdlib.h>     // exit �Լ� ���
#define MAX_STACK_SIZE 100  // ������ �ִ� ũ�⸦ 100���� ����

// ===== ���� ���� ���� ���� =====

// ���ÿ� ������ ����� �ڷ����� ������(char)
typedef char element;

// ���� ����ü ���� (�迭 ���)
typedef struct {
	element data[MAX_STACK_SIZE];  // ��ҵ��� ������ �迭
	int top;                       // ������ ���� �� ��� �ε���
} StackType;

// ���� �ʱ�ȭ �Լ� - ������ ��� �ִ� ���·� ����
void init_stack(StackType* s)
{
	s->top = -1;  // top�� -1�� �����Ͽ� ���� ���¸� ��Ÿ��
}

// ������ ��� �ִ��� Ȯ���ϴ� �Լ�
int is_empty(StackType* s)
{
	return(s->top == -1);  // top�� -1�̸� true ��ȯ
}

// ������ ���� á���� Ȯ���ϴ� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));  // top�� ������ �ε����̸� ��ȭ
}

// ���ÿ� ��� �߰� (push)
void push(StackType* s, element item)
{
	if (is_full(s)) {  // ������ ��ȭ �����̸�
		fprintf(stderr, "���� ��ȭ ����\n");  // ���� �޽��� ���
		return;  // �Լ� ����
	}
	else {
		s->data[++(s->top)] = item;  // top ���� �� �ش� ��ġ�� item ����
	}
}

// ���ÿ��� ��� ���� (pop)
element pop(StackType* s)
{
	if (is_empty(s)) {  // ������ ��� ������
		fprintf(stderr, "���� ���� ����\n");  // ���� �޽��� ���
		exit(1);  // ������ ����
	}
	else {
		return s->data[(s->top)--];  // top ��ġ�� ���� ��ȯ �� top ����
	}
}

// ������ top ��Ҹ� Ȯ�θ� �ϰ� ������ ���� (peek)
element peek(StackType* s)
{
	if (is_empty(s)) {  // ������ ��� ������
		fprintf(stderr, "���ð��鿡��\n");
		exit(1);
	}
	else {
		return s->data[s->top];  // ���� top�� ���� ��ȯ
	}
}

// ===== ���� ���� ���� �� =====

// ===== �������� �켱���� ��ȯ �Լ� =====
int prec(char op) {
	switch (op) {
	case '(': case ')': return 0;  // ��ȣ�� ���� ���� �켱����
	case '+': case '-': return 1;  // ����, ���� �켱���� 1
	case '*': case '/': return 2;  // ����, ������ �켱���� 2
	}
	return -1;  // ���ǵ��� ���� �����ڴ� -1 ��ȯ
}

// ===== ���� ������ ���� �������� ��ȯ�ϴ� �Լ� =====
void infix_to_postfix(char exp[])
{
	int i = 0;              // �ݺ��� �ε���
	char ch, top_op;        // ���� ���ڿ� ���� ��� ������ �����
	int len = strlen(exp);  // �Էµ� ������ ����
	StackType s;            // ���� ����

	init_stack(&s);         // ���� �ʱ�ȭ

	// ���� ������ �� ���ڿ� ���� ó��
	for (i = 0; i < len; i++) {
		ch = exp[i];  // ���� ���� ����

		switch (ch) {
			// �������� ���
		case '+': case '-': case '*': case '/':
			// ������ ������� �ʰ�, ���� �����ں��� �켱������ ���� �����ڰ� ���ÿ� ������ ������ ���
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
				printf("%c", pop(&s));  // pop�� ������ ���
			push(&s, ch);  // ���� �����ڴ� ���ÿ� push
			break;

		case '(':  // ���� ��ȣ�� ������ ���ÿ� push
			push(&s, ch);
			break;

		case ')':  // �ݴ� ��ȣ�� ������
			top_op = pop(&s);  // ���ÿ��� �����ڸ� ����
			// ���� ��ȣ�� ���� ������ ���ÿ��� pop�ؼ� ���
			while (top_op != '(') {
				printf("%c", top_op);
				top_op = pop(&s);
			}
			break;

		default:  // �ǿ������� ��� �ٷ� ���
			printf("%c", ch);
			break;
		}
	}

	// ������ �� ó�������� ���ÿ� ���� �ִ� �����ڵ��� ���� ���
	while (!is_empty(&s))
		printf("%c", pop(&s));
}

// ===== ���� �Լ� =====
int main(void)
{
	char* s = "(2+3)*4+9";  // �׽�Ʈ�� ���� ǥ�� ����
	printf("����ǥ�ü���: %s\n", s);  // ���� ���� ���
	printf("����ǥ�ü���: ");
	infix_to_postfix(s);  // ����ǥ�� �������� ��ȯ �� ���
	printf("\n");  // �ٹٲ�
	return 0;
}

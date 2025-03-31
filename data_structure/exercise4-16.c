#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>


//=====���� �ڵ��� ����=====
#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

//���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
}

//���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return(s->top == -1);
}
//��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
//�����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
//�����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
//��ũ�Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���ð��鿡��\n");
		exit(1);
	}
	else return s->data[s->top];
}
//===== ���� �ڵ��� �� =====

int main(void)
{
	char word[100];
	int length;
	StackType stack;
		
	printf("���ڿ��� �Է��ϼ���: ");
	scanf("%s", word);

	length = strlen(word);

	init_stack(&stack);		//���� �ʱ�ȭ

	// ���ڿ��� ���ÿ� push
	for (int i = 0; i < length; i++) {
		push(&stack, word[i]);
	}

	// ȸ�� üũ
	int is_palindrome = 1;  // 1�̸� ȸ��, 0�̸� ȸ�� �ƴ�)
	for (int i = 0; i < length; i++) {
		if (word[i] != pop(&stack)) {
			is_palindrome = 0;  // ȸ���� �ƴϸ� 0���� ����
			break;
		}
	}

	// ��� ���
	if (is_palindrome) {
		printf("ȸ���Դϴ�.\n");
	}
	else {
		printf("ȸ���� �ƴմϴ�.\n");
	}

	return 0;
}
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

	printf("���ڿ��� �Է��ϼ���: ");
	scanf("%s", word);

	length = strlen(word);

	for (int i = 0; i < length / 2; i++)
	{
		if (word[i] != word[length - 1 - i]);
	}
	return 0;
}
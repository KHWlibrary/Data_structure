#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

//���Ŀ� ������ �ʿ��ϸ� ���⸸ �����Ͽ� ���δ�.
//=====���� �ڵ��� ����=====
#define MAX_STACK_SIZE 7
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
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}
//===== ���� �ڵ��� �� =====

int main(void)
{
	StackType s;
	init_stack(&s);
	int num;
	char str[100];
	printf("���� �迭�� ũ��: %d\n", MAX_STACK_SIZE - 1); 
	printf("������ �Է��Ͻÿ�: ");
	scanf("%c", &num);
	num = atoi(str);
	
		
}
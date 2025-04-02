#include<stdio.h>
#include<stdlib.h>

//=====���� �ڵ��� ����=====
#define MAX_STACK_SIZE 100
typedef char element;
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

void process_parentheses(char* expr) {
	StackType stack;			//���� ����
	init_stack(&stack);			//���� �ʱ�ȭ
	int current_value = 0;		//�� �ʱ�ȭ
		
	for (int i = 0; expr[i] != '\0'; i++) {
		if (expr[i] == '(') {
			push(&stack, current_value); // '('�϶� ���ÿ� ���簪 ����
			current_value += 1;
			printf("%d", current_value);
		}
		else if (expr[i] == ')') {
			if (!is_empty(&stack)) {
				current_value = pop(&stack);
				printf("%d", current_value);		//�� ���
			}
			else {
				printf(" ");
				return;
			}
		}
	}
}



int main()
{
	char expr[MAX_STACK_SIZE];
	printf("��ȣ�� �Է½ÿ�: ");
	fgets(expr, MAX_STACK_SIZE, stdin);

	process_parentheses(expr);

	return 0;
}
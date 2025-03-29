#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable : 4996)

#define MAX_SIZE 5

typedef struct stack
{
	int arr[MAX_SIZE];		//스택 크기 지정
	int top;				
}stack;

void createStack(stack* p);
void push(stack* p, int element);
int pop(stack* p);
void displayStack(stack* p);
void clearStack(stack* p);

int main()
{
	int choice, value;
	stack stk; //구조체 변수 선언(스택 생성)

	createStack(&stk);

	while (1)
	{
		system("cls");
		printf("\n\n\t\t*** Stack with Array ***\n\n");
		printf("\t\t1. push    2. pop    3. print    4. clear    0. exit\n");
		printf("\t\tchoice : [ ]\b\b");
		scanf("%d", &choice);
		while (getchar() != '\n');

		switch (choice)
		{
		case 1:
			printf("\n\n\t\t정수 입력 : ");
			scanf("%d", &value);
			while (getchar() != '\n');

			push(&stk, value);
			break;
		case 2:
			value = pop(&stk); //삭제된 값을 리턴
			if (value == -1)
				printf("\n\n\t\tstack underflow\n");
			else
				printf("\n\n\t\t%d pop\n", value);
			break;
		case 3:
			displayStack(&stk);
			break;
		case 4:
			clearStack(&stk);
			break;
		case 0:
			exit(0);
		}
		printf("\n\n\t\t");
		system("pause");
	}
	return 0;
}

void createStack(stack* p)
{
	p->top = -1;
}

void push(stack* p, int element)
{
	if (p->top == MAX_SIZE - 1)
	{
		printf("\n\n\t\tstack overflow\n");
		return;
	}
	p->arr[++(p->top)] = element;
}

void displayStack(stack* p)
{
	int i;
	printf("\n\n\t\tstack display(LIFO) : ");
	for (i = p->top; i >= 0; i--)
		printf("%d ", p->arr[i]);
	puts(""); //줄바꿈
}

void clearStack(stack* p)
{
	p->top = -1;
}

int pop(stack* p)
{
	if (p->top == -1) //underflow
	{
		return -1;
	}
	//물리적인 삭제가 아니다. 논리적인 삭제
	//(p->top)--;
	return p->arr[(p->top)--];
}
?
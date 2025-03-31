#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>


//=====스택 코드의 시작=====
#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

//스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
}

//공백 상태 검출 함수
int is_empty(StackType* s)
{
	return(s->top == -1);
}
//포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
//삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
//삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
//피크함수
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택공백에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
//===== 스택 코드의 끝 =====

int main(void)
{
	char word[100];
	int length;

	printf("문자열을 입력하세요: ");
	scanf("%s", word);

	length = strlen(word);

	for (int i = 0; i < length / 2; i++)
	{
		if (word[i] != word[length - 1 - i]);
	}
	return 0;
}
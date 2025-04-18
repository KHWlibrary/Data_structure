#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

//차후에 스택이 필요하면 여기만 복사하여 붙인다.
//=====스택 코드의 시작=====
#define MAX_STACK_SIZE 7
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
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
//===== 스택 코드의 끝 =====

int main(void)
{
	StackType s;

	init_stack(&s);
	int num;
	printf("정수 배열의 크기: %d\n", MAX_STACK_SIZE -1  );		//최대 6자리 입력가능
	printf("정수를 입력하시오: ");
	scanf("%d", &num);

	if (num == 0) {
		printf("반전된 정수 배열: \n");
		return 0;
	}
	if (num < 0) {
		printf("음수는 사용하지 않습니다\n");
		return 0;
	}

	while (num > 0) {
		push(&s, num % 10);		//num%10 마지막 자리수 스택에 저장
		num /= 10;
	}
	printf("반전된 정수 배열");
	while (!is_empty(&s)) {
		printf("%d", pop(&s));
	}
	printf("\n");
	return 0;
}
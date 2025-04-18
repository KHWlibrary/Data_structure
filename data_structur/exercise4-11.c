#include<stdio.h>
#include<stdlib.h>

//=====스택 코드의 시작=====
#define MAX_STACK_SIZE 100
typedef char element;
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

void process_parentheses(char* expr) {
	StackType stack;			//스택 선언
	init_stack(&stack);			//스택 초기화
	int current_value = 0;		//값 초기화
		
	for (int i = 0; expr[i] != '\0'; i++) {
		if (expr[i] == '(') {
			push(&stack, current_value); // '('일때 스택에 현재값 저장
			current_value += 1;
			printf("%d", current_value);
		}
		else if (expr[i] == ')') {
			if (!is_empty(&stack)) {
				current_value = pop(&stack);
				printf("%d", current_value);		//값 출력
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
	printf("괄호를 입력시오: ");
	fgets(expr, MAX_STACK_SIZE, stdin);

	process_parentheses(expr);

	return 0;
}
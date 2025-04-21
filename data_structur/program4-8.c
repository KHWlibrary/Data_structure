#include<stdio.h>      // 표준 입출력 함수 사용
#include<stdlib.h>     // exit 함수 사용
#define MAX_STACK_SIZE 100  // 스택의 최대 크기를 100으로 정의

// ===== 스택 구조 정의 시작 =====

// 스택에 저장할 요소의 자료형은 문자형(char)
typedef char element;

// 스택 구조체 정의 (배열 기반)
typedef struct {
	element data[MAX_STACK_SIZE];  // 요소들을 저장할 배열
	int top;                       // 스택의 가장 위 요소 인덱스
} StackType;

// 스택 초기화 함수 - 스택을 비어 있는 상태로 설정
void init_stack(StackType* s)
{
	s->top = -1;  // top을 -1로 설정하여 공백 상태를 나타냄
}

// 스택이 비어 있는지 확인하는 함수
int is_empty(StackType* s)
{
	return(s->top == -1);  // top이 -1이면 true 반환
}

// 스택이 가득 찼는지 확인하는 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));  // top이 마지막 인덱스이면 포화
}

// 스택에 요소 추가 (push)
void push(StackType* s, element item)
{
	if (is_full(s)) {  // 스택이 포화 상태이면
		fprintf(stderr, "스택 포화 에러\n");  // 에러 메시지 출력
		return;  // 함수 종료
	}
	else {
		s->data[++(s->top)] = item;  // top 증가 후 해당 위치에 item 삽입
	}
}

// 스택에서 요소 제거 (pop)
element pop(StackType* s)
{
	if (is_empty(s)) {  // 스택이 비어 있으면
		fprintf(stderr, "스택 공백 에러\n");  // 에러 메시지 출력
		exit(1);  // 비정상 종료
	}
	else {
		return s->data[(s->top)--];  // top 위치의 값을 반환 후 top 감소
	}
}

// 스택의 top 요소를 확인만 하고 꺼내지 않음 (peek)
element peek(StackType* s)
{
	if (is_empty(s)) {  // 스택이 비어 있으면
		fprintf(stderr, "스택공백에러\n");
		exit(1);
	}
	else {
		return s->data[s->top];  // 현재 top의 값을 반환
	}
}

// ===== 스택 구조 정의 끝 =====

// ===== 연산자의 우선순위 반환 함수 =====
int prec(char op) {
	switch (op) {
	case '(': case ')': return 0;  // 괄호는 가장 낮은 우선순위
	case '+': case '-': return 1;  // 덧셈, 뺄셈 우선순위 1
	case '*': case '/': return 2;  // 곱셈, 나눗셈 우선순위 2
	}
	return -1;  // 정의되지 않은 연산자는 -1 반환
}

// ===== 중위 수식을 후위 수식으로 변환하는 함수 =====
void infix_to_postfix(char exp[])
{
	int i = 0;              // 반복문 인덱스
	char ch, top_op;        // 현재 문자와 스택 상단 연산자 저장용
	int len = strlen(exp);  // 입력된 수식의 길이
	StackType s;            // 스택 선언

	init_stack(&s);         // 스택 초기화

	// 중위 수식의 각 문자에 대해 처리
	for (i = 0; i < len; i++) {
		ch = exp[i];  // 현재 문자 추출

		switch (ch) {
			// 연산자인 경우
		case '+': case '-': case '*': case '/':
			// 스택이 비어있지 않고, 현재 연산자보다 우선순위가 높은 연산자가 스택에 있으면 꺼내서 출력
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
				printf("%c", pop(&s));  // pop한 연산자 출력
			push(&s, ch);  // 현재 연산자는 스택에 push
			break;

		case '(':  // 여는 괄호는 무조건 스택에 push
			push(&s, ch);
			break;

		case ')':  // 닫는 괄호가 나오면
			top_op = pop(&s);  // 스택에서 연산자를 꺼냄
			// 여는 괄호를 만날 때까지 스택에서 pop해서 출력
			while (top_op != '(') {
				printf("%c", top_op);
				top_op = pop(&s);
			}
			break;

		default:  // 피연산자인 경우 바로 출력
			printf("%c", ch);
			break;
		}
	}

	// 수식을 다 처리했으면 스택에 남아 있는 연산자들을 전부 출력
	while (!is_empty(&s))
		printf("%c", pop(&s));
}

// ===== 메인 함수 =====
int main(void)
{
	char* s = "(2+3)*4+9";  // 테스트할 중위 표기 수식
	printf("중위표시수식: %s\n", s);  // 중위 수식 출력
	printf("후위표시수식: ");
	infix_to_postfix(s);  // 후위표기 수식으로 변환 및 출력
	printf("\n");  // 줄바꿈
	return 0;
}

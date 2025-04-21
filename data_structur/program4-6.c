#include<stdio.h>       // 표준 입출력 함수 사용을 위한 헤더
#include<stdlib.h>      // 동적 메모리, exit 함수 등을 위한 헤더
#include<string.h>      // 문자열 처리 함수 (strlen) 사용을 위한 헤더

#define MAX_STACK_SIZE 100   // 스택에 저장할 수 있는 최대 요소 개수

// ===== 스택 자료구조 정의 =====
typedef char element;   // 스택에 저장할 요소를 문자형(char)으로 정의

// 구조체로 스택 정의 (고정 크기 배열 사용)
typedef struct {
	element data[MAX_STACK_SIZE];  // 스택 요소들을 저장할 배열
	int top;                       // 스택의 가장 위(top) 요소의 인덱스
} StackType;

// ===== 스택 관련 함수들 =====

// 스택을 초기화하는 함수 (처음엔 top이 -1, 즉 비어 있음)
void init_stack(StackType* s)
{
	s->top = -1;
}

// 스택이 비어 있는지 확인하는 함수
int is_empty(StackType* s)
{
	return(s->top == -1);  // top이 -1이면 공백 상태
}

// 스택이 가득 찼는지 확인하는 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));  // top이 배열 끝이면 포화 상태
}

// 스택에 요소를 추가하는 함수 (삽입 - push 연산)
void push(StackType* s, element item)
{
	if (is_full(s)) {  // 포화 상태이면 오류 메시지 출력
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else {
		// top을 하나 증가시킨 후 해당 위치에 item 저장
		s->data[++(s->top)] = item;
	}
}

// 스택에서 요소를 꺼내는 함수 (삭제 - pop 연산)
element pop(StackType* s)
{
	if (is_empty(s)) {  // 공백 상태면 꺼낼 게 없으므로 오류 출력
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);  // 프로그램 강제 종료
	}
	else {
		// top 위치의 요소를 반환하고, top을 감소시킴
		return s->data[(s->top)--];
	}
}

// 스택의 top 요소를 꺼내지 않고 반환 (peek 연산)
element peek(StackType* s)
{
	if (is_empty(s)) {  // 스택이 비어 있으면 오류 출력
		fprintf(stderr, "스택공백에러\n");
		exit(1);
	}
	else {
		// 현재 top 위치의 요소를 반환만 (삭제는 하지 않음)
		return s->data[s->top];
	}
}

// ===== 괄호 짝 검사 함수 =====

// 괄호가 올바르게 짝지어졌는지 확인하는 함수
int check_matching(const char* in)
{
	StackType s;           // 스택 선언
	char ch, open_ch;      // 현재 문자, 스택에서 꺼낸 여는 괄호 저장 변수
	int i, n = strlen(in); // 문자열 길이 계산
	init_stack(&s);        // 스택 초기화

	// 문자열의 각 문자들을 하나씩 확인
	for (i = 0; i < n; i++) {
		ch = in[i];  // 현재 문자 하나를 ch에 저장

		// 여는 괄호인 경우 → 스택에 push
		switch (ch) {
		case '(': case '[': case '{':
			push(&s, ch);  // 스택에 저장
			break;

			// 닫는 괄호인 경우
		case ')': case ']': case '}':
			if (is_empty(&s)) return 0;  // 스택이 비어있으면 짝이 안 맞음

			open_ch = pop(&s);  // 여는 괄호 꺼내서
			// 짝이 맞는지 비교
			if ((open_ch == '(' && ch != ')') ||
				(open_ch == '[' && ch != ']') ||
				(open_ch == '{' && ch != '}')) {
				return 0;  // 짝이 안 맞으면 실패
			}
			break;
		}
	}

	// 반복이 끝난 후에도 스택에 남아있다면 짝이 안 맞은 여는 괄호가 있음
	if (!is_empty(&s)) return 0;

	// 모든 괄호가 정상적으로 닫혔으면 성공
	return 1;
}

// ===== 메인 함수 =====
int main(void)
{
	// 괄호 짝이 맞는지 검사할 문자열
	char* p = "{[(())]}";

	// 검사 결과 출력
	if (check_matching(p) == 1)
		printf("%s 괄호 검사 성공\n", p);
	else
		printf("%s 괄호 검사 실패\n", p);

	return 0;
}

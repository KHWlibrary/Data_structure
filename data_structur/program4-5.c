#include<stdio.h>      // 표준 입출력 함수 사용을 위한 헤더 파일
#include<stdlib.h>     // 메모리 동적 할당 및 일반적인 유틸리티 함수 사용을 위한 헤더 파일

#define MAX_STACK_SIZE 100   // (현재 코드에선 사용되지 않지만) 스택의 최대 크기를 지정하는 매크로

typedef int element;         // element를 int로 정의하여 코드 가독성 향상

// 동적 스택 구현을 위한 구조체 정의
typedef struct {
	element* data;      // 스택 요소들을 저장할 포인터 (동적 배열)
	int capacity;       // 스택의 현재 용량
	int top;            // 스택의 top 인덱스 (가장 마지막에 삽입된 요소의 위치)
} StackType;

// 스택 초기화 함수: 초기 용량을 1로 설정하고 메모리 할당
void init_stack(StackType* s)
{
	s->top = -1;  // 초기에는 스택이 비어 있으므로 top을 -1로 설정
	s->capacity = 1;  // 초기 용량을 1로 설정
	s->data = (element*)malloc(s->capacity * sizeof(element));  // 동적 메모리 할당
}

// 스택이 비어 있는지 확인하는 함수
int is_empty(StackType* s)
{
	return(s->top == -1);  // top이 -1이면 비어 있는 상태
}

// 스택이 가득 찼는지 확인하는 함수
int is_full(StackType* s)
{
	return(s->top == (s->capacity - 1));  // top이 용량의 마지막 위치에 있으면 포화 상태
}

// 스택에 요소를 추가하는 함수 (필요시 용량을 두 배로 늘림)
void push(StackType* s, element item)
{
	if (is_full(s)) {  // 스택이 꽉 찼다면
		s->capacity *= 2;  // 용량을 두 배로 증가
		s->data = (element*)realloc(s->data, s->capacity * sizeof(element));  // 재할당
	}
	s->data[++(s->top)] = item;  // top을 증가시키고 해당 위치에 item 삽입
}

// 스택에서 요소를 제거하고 반환하는 함수
element pop(StackType* s)
{
	if (is_empty(s)) {  // 스택이 비어 있으면
		fprintf(stderr, "스택 공백 에러\n");  // 에러 메시지 출력
		exit(1);  // 비정상 종료
	}
	else return s->data[(s->top)--];  // top 위치의 요소를 반환하고 top 감소
}

// 메인 함수: 스택 테스트
int main(void)
{
	StackType s;          // 스택 변수 선언
	init_stack(&s);       // 스택 초기화

	push(&s, 1);          // 스택에 1 추가
	push(&s, 2);          // 스택에 2 추가
	push(&s, 3);          // 스택에 3 추가

	printf("%d \n", pop(&s));  // 3 출력 (가장 마지막에 추가된 값)
	printf("%d \n", pop(&s));  // 2 출력
	printf("%d \n", pop(&s));  // 1 출력

	free(s.data);         // 동적 할당한 메모리 해제
	return 0;             // 프로그램 종료
}

#include<stdio.h>     // 표준 입출력 함수 사용을 위한 헤더 파일
#include<stdlib.h>    // 일반적인 유틸리티 함수들(예: exit 함수 등)을 위한 헤더 파일

#define MAX_STACK_SIZE 100   // 스택의 최대 크기를 100으로 정의
typedef int element;         // element를 int형으로 정의하여 코드 가독성 향상
element stack[MAX_STACK_SIZE];  // 정적 배열로 구현한 스택
int top = -1;                // 스택의 top을 -1로 초기화하여 빈 스택 상태로 설정

// 공백 상태를 검사하는 함수
int is_empty()
{
	return(top == -1);       // top이 -1이면 스택이 비어있는 상태
}

// 포화 상태를 검사하는 함수
int is_full()
{
	return(top == (MAX_STACK_SIZE - 1)); // top이 최대 인덱스에 도달했는지 확인
}

// 스택에 데이터를 삽입하는 함수 (push)
void push(element item)
{
	if (is_full()) {         // 스택이 가득 찼는지 확인
		fprintf(stderr, "스택 포화 에러\n"); // 에러 메시지 출력
		return;               // 함수 종료
	}
	else stack[++top] = item;  // top을 증가시키고 해당 위치에 item 저장
}

// 스택에서 데이터를 삭제하고 반환하는 함수 (pop)
element pop()
{
	if (is_empty()) {        // 스택이 비어있는지 확인
		fprintf(stderr, "스택 공백 에러"); // 에러 메시지 출력
		exit(1);             // 프로그램 비정상 종료
	}
	else return stack[top--]; // top 위치의 데이터를 반환하고 top 감소
}

// 스택의 top 요소를 반환하되 삭제하지 않는 함수 (peek)
element peek()
{
	if (is_empty()) {        // 스택이 비어있는지 확인
		fprintf(stderr, "스택 공백 에러"); // 에러 메시지 출력
		exit(1);             // 프로그램 비정상 종료
	}
	else return stack[top];  // top 위치의 데이터를 그대로 반환
}

// 메인 함수: 스택 사용 예시
int main(void)
{
	push(1);                 // 스택에 1 추가
	push(2);                 // 스택에 2 추가
	push(3);                 // 스택에 3 추가

	printf("%d\n", pop());   // 스택에서 가장 위의 요소(3)를 제거하고 출력
	printf("%d\n", pop());   // 다음 요소(2)를 제거하고 출력
	printf("%d\n", pop());   // 마지막 요소(1)를 제거하고 출력

	return 0;                // 프로그램 종료
}

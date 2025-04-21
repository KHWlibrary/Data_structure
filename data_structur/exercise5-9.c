// 2개의 스택을 사용하여 큐를 구현해보자.
// 입력이 들어오면 스택 #1에 넣는다.
// 출력 요청이 들어오면 스택 #2에서 요소를 꺼낸다.
// 스택 #2가 비어있을 때는 스택 #1의 모든 요소를 꺼내서 스택 #2에 넣는다.

#define _CRT_SECURE_NO_WARNINGS     // scanf 보안 경고 제거용
#include <stdio.h>                  // 표준 입출력 함수
#include <stdlib.h>                 // exit 함수 등 표준 라이브러리

#define MAX_STACK_SIZE 100          // 스택 하나의 최대 크기 설정

// 스택에 저장될 데이터 타입 정의 (정수형)
typedef int element;

// 스택 구조체 정의
typedef struct {
	element data[MAX_STACK_SIZE];  // 데이터를 저장할 배열
	int top;                       // top은 현재 스택의 꼭대기를 가리킴
} StackType;

// 스택을 초기화하는 함수
void init_stack(StackType* s) {
	s->top = -1;                   // 초기에는 아무것도 없으므로 -1로 설정
}

// 스택이 비어있는지 확인하는 함수
int is_empty(StackType* s) {
	return (s->top == -1);        // top이 -1이면 비어있음
}

// 스택이 가득 찼는지 확인하는 함수
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));  // top이 최대 인덱스에 도달했는지 확인
}

// 스택에 데이터를 삽입하는 함수 (push)
void push(StackType* s, element item) {
	if (is_full(s)) {             // 가득 찬 경우 에러 출력
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	s->data[++(s->top)] = item;  // top을 1 증가시키고 해당 위치에 값 저장
}

// 스택에서 데이터를 제거하는 함수 (pop)
element pop(StackType* s) {
	if (is_empty(s)) {           // 비어있는 경우 에러 출력 후 종료
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	return s->data[(s->top)--];  // 현재 top의 값을 반환하고 top을 감소
}

// 스택의 최상단 값을 확인하는 함수 (peek)
element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	return s->data[s->top];      // top 위치의 값만 반환 (삭제하지 않음)
}

// 스택 1의 내용을 출력하는 함수 (bottom → top)
void print1(StackType* ps) {
	if (is_empty(ps)) return;    // 비어있으면 아무것도 출력하지 않음
	for (int i = 0; i <= ps->top; i++)  // 아래부터 위까지 순차 출력
		printf("%d ", ps->data[i]);
}

// 스택 2의 내용을 출력하는 함수 (top → bottom)
void print2(StackType* ps) {
	if (is_empty(ps)) return;    // 비어있으면 아무것도 출력하지 않음
	for (int i = ps->top; i >= 0; i--)  // 위에서 아래로 출력
		printf("%d ", ps->data[i]);
}

// 메인 함수 - 큐를 스택 2개로 구현한 인터페이스
int main() {
	StackType s1, s2;            // 스택 2개 생성
	init_stack(&s1);             // s1 초기화
	init_stack(&s2);             // s2 초기화

	int select;                  // 사용자 메뉴 선택용 변수
	element data;                // 삽입할 데이터

	while (1) {                  // 무한 루프 - 종료 조건에서 빠져나감
		printf("1.삽입 | 2.삭제 | 3.출력 | 4.종료: ");
		scanf("%d", &select);   // 사용자로부터 선택 입력

		switch (select) {
		case 1:  // 삽입 연산
			printf("정수를 입력하세요: ");
			scanf("%d", &data); // 데이터 입력
			push(&s1, data);    // 스택 1에 push (enqueue 개념)
			break;

		case 2:  // 삭제 연산
			if (is_empty(&s2)) {              // 스택 2가 비어있다면
				while (!is_empty(&s1)) {      // 스택 1이 비어있지 않을 동안
					push(&s2, pop(&s1));      // 스택 1의 모든 데이터를 스택 2로 옮김
				}
			}
			if (!is_empty(&s2)) {             // 스택 2가 비어있지 않다면
				printf("삭제된 값: %d\n", pop(&s2)); // s2에서 데이터 꺼내기 (dequeue 개념)
			}
			else {
				printf("큐가 비어 있습니다.\n"); // 둘 다 비어있으면 출력 불가
			}
			break;

		case 3:  // 출력 연산 (큐 상태 보기)
			printf("큐 상태 (front -> rear): ");
			print2(&s2); // 스택 2의 top이 front 역할
			print1(&s1); // 스택 1의 bottom이 rear 역할
			printf("\n");
			break;

		case 4:  // 종료
			return 0;    // 프로그램 정상 종료

		default:
			printf("올바른 메뉴를 선택하세요.\n"); // 잘못된 입력 처리
		}
	}
}

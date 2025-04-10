#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화
void init_stack(StackType* s) {
	s->top = -1;
}

// 공백 상태
int is_empty(StackType* s) {
	return (s->top == -1);
}

// 포화 상태
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입
void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	s->data[++(s->top)] = item;
}

// 삭제
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	return s->data[(s->top)--];
}

// 피크
element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	return s->data[s->top];
}

// 스택1: 하단부터 상단까지 출력
void print1(StackType* ps) {
	if (is_empty(ps)) return;
	for (int i = 0; i <= ps->top; i++)
		printf("%d ", ps->data[i]);
}

// 스택2: 상단부터 하단까지 출력
void print2(StackType* ps) {
	if (is_empty(ps)) return;
	for (int i = ps->top; i >= 0; i--)
		printf("%d ", ps->data[i]);
}

int main() {
	StackType s1, s2;
	init_stack(&s1);
	init_stack(&s2);

	int select;
	element data;

	while (1) {
		printf("1.삽입 | 2.삭제 | 3.출력 | 4.종료: ");
		scanf("%d", &select);

		switch (select) {
		case 1:
			printf("정수를 입력하세요: ");
			scanf("%d", &data);
			push(&s1, data);
			break;
		case 2:
			if (is_empty(&s2)) {
				while (!is_empty(&s1)) {
					push(&s2, pop(&s1));
				}
			}
			if (!is_empty(&s2)) {
				printf("삭제된 값: %d\n", pop(&s2));
			}
			else {
				printf("큐가 비어 있습니다.\n");
			}
			break;
		case 3:
			printf("큐 상태 (front -> rear): ");
			print2(&s2);  // s2가 front 쪽
			print1(&s1);  // s1이 rear 쪽
			printf("\n");
			break;
		case 4:
			return 0;
		default:
			printf("올바른 메뉴를 선택하세요.\n");
		}
	}
}

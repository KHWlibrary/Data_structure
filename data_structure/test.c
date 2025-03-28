#define _CRT_SECURE_NO_WARNINGS  // 꼭 맨 위에 넣어야 함
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return s->top == -1;
}

int is_full(StackType* s) {
	return s->top == MAX_STACK_SIZE - 1;
}

void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		exit(1);
	}
	s->data[++(s->top)] = item;
}

element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	return s->data[(s->top)--];
}

int main(void) {
	StackType s;
	init_stack(&s);

	int num;
	printf("정수를 입력하시오: ");
	scanf("%d", &num);  // ?? scanf_s 도 가능하나, scanf로 써도 경고만 나고 실행됩니다

	if (num == 0) {
		printf("반전된 정수: 0\n");
		return 0;
	}
	if (num < 0) {
		printf("음수는 사용하지 않습니다.\n");
		return 0;
	}

	int original = num;

	while (num > 0) {
		push(&s, num % 10);  // 자릿수를 스택에 저장
		num /= 10;
	}

	printf("입력한 정수: %d\n", original);
	printf("반전된 정수: ");
	while (!is_empty(&s)) {
		printf("%d", pop(&s));  // 스택에서 꺼내며 거꾸로 출력
	}
	printf("\n");

	return 0;
}

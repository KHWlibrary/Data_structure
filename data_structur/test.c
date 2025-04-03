#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

// 스택 구조체 정의
typedef struct {
    char data[MAX_SIZE];  // 문자 스택
    int count[MAX_SIZE];  // 문자의 개수를 저장하는 배열
    int top;              // 스택의 상단을 나타내는 변수
} Stack;

// 스택 초기화 함수
void initStack(Stack* stack) {
    stack->top = -1;  // 스택이 비어있을 때 top은 -1
}

// 스택에 요소를 추가하는 함수
void push(Stack* stack, char c, int cnt) {
    if (stack->top < MAX_SIZE - 1) {
        stack->top++;
        stack->data[stack->top] = c;
        stack->count[stack->top] = cnt;
    }
}

// 스택에서 요소를 제거하는 함수
void pop(Stack* stack) {
    if (stack->top >= 0) {
        stack->top--;
    }
}

// 스택의 top 요소를 반환하는 함수
char peekChar(Stack* stack) {
    return stack->data[stack->top];
}

// 스택의 top에 있는 개수를 반환하는 함수
int peekCount(Stack* stack) {
    return stack->count[stack->top];
}

// 문자열 압축 함수
void compressString(const char* input) {
    Stack stack;
    initStack(&stack);

    int len = strlen(input);

    for (int i = 0; i < len; i++) {
        if (stack.top == -1 || peekChar(&stack) != input[i]) {
            push(&stack, input[i], 1);  // 새로운 문자를 스택에 넣음
        }
        else {
            stack.count[stack.top]++;  // 연속된 문자의 개수 증가
        }
    }

    // 압축된 문자열 출력
    for (int i = 0; i <= stack.top; i++) {
        printf("%d%c", stack.count[i], stack.data[i]);
    }
    printf("\n");
}

int main() {
    char input[MAX_SIZE];

    // 사용자로부터 문자열 입력 받기
    printf("문자열을 입력하세요: ");
    scanf("%s", input);

    for (int i = 0; input[i] != '\0'; i++) {
        input[i] = tolower(input[i]);  // 대문자를 소문자로 변환
    }

    // 압축된 문자열 출력
    printf("압축된 문자열: ");
    compressString(input);

    return 0;
}
